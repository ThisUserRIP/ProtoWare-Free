#include "pch.h"
#include "fast_raycast.h"
#include "gameoffsets.h" 
#include "game.h" 
#include "minhook.h" 
#include <mdPhysics.hpp>
#include <internal_transform.h>
#include <internal_gameobject.h>
#include <internal_component.h>
#include <component.h>
#include <mdRaycastHit.hpp>
#include <stPlayerHitboxData.hpp>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

uintptr fast_raycast_map;
uintptr_t cached_chunks_ptr = 0; 
int map_min_x, map_min_y, map_min_z;
int map_max_x, map_max_y, map_max_z;
int map_size_x, map_size_y;
uintptr_t cached_array_list = 0;

std::unordered_map<uint64_t, CachedChunk> chunk_cache;
std::shared_mutex cache_mutex;
uintptr_t fluid_class_ptr = 0;

typedef void(__fastcall* DELEGATE_SetDirty)(uintptr_t chunkRenderer, uintptr_t method);
typedef void(__fastcall* DELEGATE_SetBlockAndRecompute)(uintptr_t map, uintptr_t blockData, vec3i* pos, uintptr_t method);
DELEGATE_SetDirty setdirty_o = nullptr;
DELEGATE_SetBlockAndRecompute setblockandrecompute_o = nullptr;

void __fastcall hkSetDirty(uintptr_t chunkRenderer, uintptr_t method);
void __fastcall hkSetBlockAndRecompute(uintptr_t map, uintptr_t blockData, vec3i* pos, uintptr_t method);

namespace offsets {
    constexpr uintptr_t Map_chunks = 0x48;
    constexpr uintptr_t Chunk_blocks = 0x10;
    constexpr uintptr_t Chunk_position = 0x18;
    constexpr uintptr_t ChunkRenderer_chunk = 0x10;

    constexpr uintptr_t List3D_list = 0x10; 
    constexpr uintptr_t List3D_min = 0x10; 

    constexpr uintptr_t Map_Chunks = 0x48;       
    constexpr uintptr_t Chunk_Blocks = 0x10;     
    constexpr uintptr_t Chunk_Position = 0x18;   
    constexpr uintptr_t ChunkRenderer_Chunk = 0x10; 

    constexpr uintptr_t List3D_List = 0x10;      
    constexpr uintptr_t List3D_Bounds = 0x10;
}

inline uint64_t get_chunk_hash(int x, int y, int z) {
    return ((uint64_t)(x & 0xFFFFF)) | (((uint64_t)(y & 0xFFFFF)) << 20) | (((uint64_t)(z & 0xFFFFF)) << 40);
}
bool is_block_solid(uintptr_t block_ptr) {
    if (!block_ptr) return false;

    uintptr_t klass = *(uintptr_t*)block_ptr;

    if (fluid_class_ptr && klass == fluid_class_ptr) {
        return false;
    }

    if (!fluid_class_ptr) {
        const char* name = *(const char**)(klass + 0x10);
        if (name && strcmp(name, "FluidBlock") == 0) {
            fluid_class_ptr = klass;
            return false;
        }
    }

    return true;
}

void fast_raycast::initialize() {
    rebuild_all();
    MH_CreateHook((void*)(gameassembly + 0x650a80), &hkSetDirty, (void**)&setdirty_o);
    MH_CreateHook((void*)(gameassembly + 0x657660), &hkSetBlockAndRecompute, (void**)&setblockandrecompute_o);
    MH_EnableHook((void*)(gameassembly + 0x650a80));
    MH_EnableHook((void*)(gameassembly + 0x657660));
}

void fast_raycast::update() {
    fast_raycast_map = game::get_map();
    if (!fast_raycast_map) {
        cached_chunks_ptr = 0;
        return;
    }

    cached_chunks_ptr = *(uintptr_t*)(fast_raycast_map + 0x48); 
    if (cached_chunks_ptr) {
        map_min_x = *(int*)(cached_chunks_ptr + 0x18);
        map_min_y = *(int*)(cached_chunks_ptr + 0x1C);
        map_min_z = *(int*)(cached_chunks_ptr + 0x20);

        map_max_x = *(int*)(cached_chunks_ptr + 0x24);
        map_max_y = *(int*)(cached_chunks_ptr + 0x28);
        map_max_z = *(int*)(cached_chunks_ptr + 0x2C);

        map_size_x = map_max_x - map_min_x;
        map_size_y = map_max_y - map_min_y;

        cached_array_list = *(uintptr_t*)(cached_chunks_ptr + 0x10);
    }
}

bool intersect_triangle(const vec3& orig, const vec3& dir, const Triangle& tri, float& t, float max_dist) {
    const float EPSILON = 1e-7f;
    vec3 edge1 = tri.v1 - tri.v0;
    vec3 edge2 = tri.v2 - tri.v0;
    vec3 h = dir.cross(edge2);
    float a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON) return false;

    float f = 1.0f / a;
    vec3 s = orig - tri.v0;
    float u = f * s.dot(h);
    if (u < 0.0f || u > 1.0f) return false;

    vec3 q = s.cross(edge1);
    float v = f * dir.dot(q);
    if (v < 0.0f || u + v > 1.0f) return false;

    t = f * edge2.dot(q);
    return (t > EPSILON && t <= max_dist);
}

void fast_raycast::rebuild_chunk(uintptr_t chunk_ptr) {
    if (!chunk_ptr) return;

    vec3i pos = *(vec3i*)(chunk_ptr + offsets::Chunk_Position);

    uintptr_t blocks_container = *(uintptr_t*)(chunk_ptr + offsets::Chunk_Blocks);
    if (!blocks_container) return; 

    uintptr_t blocks_array_base = blocks_container + 0x20;

    bool solid_mask[16][16][16];

    for (int ix = 0; ix < 16; ++ix) {
        for (int iy = 0; iy < 16; ++iy) {
            for (int iz = 0; iz < 16; ++iz) {
                int index = iz + 16 * (iy + 16 * ix);

                uintptr_t block_struct_ptr = blocks_array_base + (index * 16);
                uintptr_t block_obj = *(uintptr_t*)block_struct_ptr;

                solid_mask[ix][iy][iz] = is_block_solid(block_obj);
            }
        }
    }

    CachedChunk new_cache;
    new_cache.position = pos;
    new_cache.min_world = vec3((float)pos.x * 16, (float)pos.y * 16, (float)pos.z * 16);
    new_cache.max_world = new_cache.min_world + 16.0f;
    new_cache.valid = true;
    new_cache.mesh.reserve(256); 

    for (int d = 0; d < 3; ++d) {
        int u = (d + 1) % 3;
        int v = (d + 2) % 3;
        int x[3] = { 0 };
        int q[3] = { 0 };

        bool mask[16][16]; 

        q[d] = 1;

        for (x[d] = -1; x[d] < 16; ) {
            int n = 0;

            for (x[v] = 0; x[v] < 16; ++x[v]) {
                for (x[u] = 0; x[u] < 16; ++x[u]) {
                    bool b1 = (x[d] >= 0) ? solid_mask[x[0]][x[1]][x[2]] : false;
                    bool b2 = (x[d] < 15) ? solid_mask[x[0] + q[0]][x[1] + q[1]][x[2] + q[2]] : false;
                    mask[x[u]][x[v]] = (b1 != b2);
                }
            }

            ++x[d];

            for (int j = 0; j < 16; ++j) {
                for (int i = 0; i < 16; ) {
                    if (mask[i][j]) {
                        int w, h;
                        for (w = 1; i + w < 16 && mask[i + w][j]; ++w);
                        for (h = 1; j + h < 16; ++h) {
                            for (int k = 0; k < w; ++k) {
                                if (!mask[i + k][j + h]) goto end_h;
                            }
                        }
                    end_h:;

                        x[u] = i; x[v] = j;
                        int du[3] = { 0 }; du[u] = w;
                        int dv[3] = { 0 }; dv[v] = h;

                        vec3 v0((float)x[0], (float)x[1], (float)x[2]);
                        vec3 vd_u((float)du[0], (float)du[1], (float)du[2]);
                        vec3 vd_v((float)dv[0], (float)dv[1], (float)dv[2]);

                        v0 += new_cache.min_world;

                        Triangle t1, t2;

                        t1 = { v0 - vec3(0, 0.5f, 0), v0 + vd_u - vec3(0, 0.5f, 0), v0 + vd_u + vd_v - vec3(0, 0.5f, 0)};
                        t2 = { v0 - vec3(0, 0.5f, 0), v0 + vd_u + vd_v - vec3(0, 0.5f, 0), v0 + vd_v - vec3(0, 0.5f, 0) };

                        new_cache.mesh.push_back(t1);
                        new_cache.mesh.push_back(t2);

                        for (int l = 0; l < h; ++l)
                            for (int k = 0; k < w; ++k)
                                mask[i + k][j + l] = false;

                        i += w;
                    }
                    else {
                        i++;
                    }
                }
            }
        }
    }

    {
        std::unique_lock<std::shared_mutex> lock(cache_mutex);
        chunk_cache[get_chunk_hash(pos.x, pos.y, pos.z)] = std::move(new_cache);
    }
}

void fast_raycast::rebuild_chunk_by_pos(int x, int y, int z) {
    uintptr_t map = game::get_map();
    if (!map) return;

    uintptr_t chunks_list = *(uintptr_t*)(map + offsets::Map_Chunks);
    if (!chunks_list) return;

    uintptr_t bounds = *(uintptr_t*)(chunks_list + offsets::List3D_Bounds);
    if (!bounds) return;

    int size_x = *(int*)(bounds + 0x20);
    int size_y = *(int*)(bounds + 0x10);
    int size_z = *(int*)(bounds + 0x00);

    if (x < 0 || y < 0 || z < 0) return;
    if (x >= size_x || y >= size_y || z >= size_z) return;

    int idx = (z * size_y * size_x) + (y * size_x) + x;

    uintptr_t list_array = *(uintptr_t*)(chunks_list + offsets::List3D_List);
    if (!list_array) return;

    uintptr_t chunk_ptr_loc = list_array + 0x20 + (idx * 8);
    uintptr_t chunk_ptr = *(uintptr_t*)chunk_ptr_loc;

    if (chunk_ptr) {
        rebuild_chunk(chunk_ptr);
    }
}

void fast_raycast::clear_cache() {
    std::unique_lock<std::shared_mutex> lock(cache_mutex);
    chunk_cache.clear();
    fluid_class_ptr = 0;
}

void fast_raycast::rebuild_all() {
    uintptr_t map = game::get_map();
    if (!map) return;

    uintptr_t chunks_list_ptr = *(uintptr_t*)(map + offsets::Map_chunks);
    if (!chunks_list_ptr) return;

    uintptr_t backing_array = *(uintptr_t*)(chunks_list_ptr + 0x18); 
    if (!backing_array) return;

    int array_size = *(int*)(backing_array + 0x18); 

    for (int i = 0; i < array_size; i++) {
        uintptr_t chunk = *(uintptr_t*)(backing_array + 0x20 + i * 8);
        if (chunk) {
            rebuild_chunk(chunk);
        }
    }
}

__forceinline bool contains_block_internal(int x, int y, int z) {
    if (!fast_raycast_map) return true;

    vec3i pos = vec3i(x, y, z);
    uintptr kal[3];
    kal[0] = 0; kal[1] = 0; kal[2] = 0;

    ((void(__fastcall*)(uintptr, uintptr, uintptr))(gameassembly + map_getblock_offset))((uintptr)&kal, fast_raycast_map, (uintptr)&pos);
    return isptrvalid(kal[0]);

    //if (!cached_chunks_ptr || !cached_array_list) return false;
    //
    //int cx = x >> 4;
    //int cy = y >> 4;
    //int cz = z >> 4;
    //
    //if (cx < map_min_x || cx >= map_max_x ||
    //    cy < map_min_y || cy >= map_max_y ||
    //    cz < map_min_z || cz >= map_max_z) {
    //    return false;
    //}
    //
    //int dx = cx - map_min_x;
    //int dy = cy - map_min_y;
    //int dz = cz - map_min_z;
    //
    //int chunk_index = dx + map_size_x * (dy + map_size_y * dz);
    //
    //uintptr_t chunk_obj = *(uintptr_t*)(cached_array_list + 0x20 + (chunk_index * 8));
    //if (!chunk_obj) return false;
    //
    //int bx = x & 15;
    //int by = y & 15;
    //int bz = z & 15;
    //
    //int block_idx = bz + 16 * (by + 16 * bx);
    //
    //uintptr_t block_data_array = *(uintptr_t*)(chunk_obj + 0x10);
    //if (!block_data_array) return false;
    //
    //uintptr_t block_address = block_data_array + 0x20 + (block_idx * 16);
    //
    //return isptrvalid(*(uintptr_t*)block_address);
}

bool fast_raycast::slow_raycast(vec3 start, vec3 end, int layermask) {
    ray3d ray;
    ray.origin = start;
    ray.direction = (end - start).get_normalized();
    float dist = start.get_distance(end);

    rayhit3d hit;
    if (Physics__Raycast((uintptr)&ray, (uintptr)&hit, dist, layermask)) {
        return true;
        //internal_transform* hittrs = (internal_transform*)((component*)RaycastHit__get_transform((uintptr)&hit))->internal_component;
        //PlayerHitBoxData* data = (PlayerHitBoxData*)hittrs->go->get_component("PlayerHitBoxData");
        //if (!data) return true;
    }
    return false;
}

bool fast_raycast::contains_block(vec3i block) {
    return contains_block_internal(block.x, block.y, block.z);
}
bool fast_raycast::contains_block(vec3 block) {
    return contains_block_internal(block.x, block.y, block.z);
}
bool fast_raycast::contains_block(int x, int y, int z) {
    return contains_block_internal(x, y, z);
}

bool fast_raycast::linecast(const vec3& start, const vec3& end) {
    const float EPS_DIST = 1e-6f;
    const float TIE_EPS = 1e-6f;

    vec3 dir = end - start;
    float distance = start.get_distance(end);
    if (distance < EPS_DIST) return false;
    dir = dir.get_normalized();

    vec3 s = start;
    int ix = (int)std::floor(s.x);
    int iy = (int)std::floor(s.y);
    int iz = (int)std::floor(s.z);

    if (contains_block(ix, iy, iz)) return true;

    int stepX = (dir.x > 0.0f ? 1 : (dir.x < 0.0f ? -1 : 0));
    int stepY = (dir.y > 0.0f ? 1 : (dir.y < 0.0f ? -1 : 0));
    int stepZ = (dir.z > 0.0f ? 1 : (dir.z < 0.0f ? -1 : 0));

    float tDeltaX = (stepX == 0) ? FLT_MAX : fabsf(1.0f / dir.x);
    float tDeltaY = (stepY == 0) ? FLT_MAX : fabsf(1.0f / dir.y);
    float tDeltaZ = (stepZ == 0) ? FLT_MAX : fabsf(1.0f / dir.z);

    auto compute_tmax = [&](float scoord, int i, int step, float dcomp) -> float {
        if (step > 0) return ((i + 1.0f) - scoord) / dcomp;
        if (step < 0) return (scoord - i) / -dcomp;
        return FLT_MAX;
        };

    float tMaxX = compute_tmax(s.x, ix, stepX, dir.x);
    float tMaxY = compute_tmax(s.y, iy, stepY, dir.y);
    float tMaxZ = compute_tmax(s.z, iz, stepZ, dir.z);

    while (true) {
        float tMin = std::min(tMaxX, std::min(tMaxY, tMaxZ));
        if (tMin > distance) break;

        bool stepXThis = fabsf(tMaxX - tMin) <= TIE_EPS;
        bool stepYThis = fabsf(tMaxY - tMin) <= TIE_EPS;
        bool stepZThis = fabsf(tMaxZ - tMin) <= TIE_EPS;

        int oldX = ix, oldY = iy, oldZ = iz;

        if (stepXThis) { ix += stepX; tMaxX += tDeltaX; }
        if (stepYThis) { iy += stepY; tMaxY += tDeltaY; }
        if (stepZThis) { iz += stepZ; tMaxZ += tDeltaZ; }

        if (tMin > distance) break;

        int dxs[2] = { 0, stepXThis ? stepX : 0 };
        int dys[2] = { 0, stepYThis ? stepY : 0 };
        int dzs[2] = { 0, stepZThis ? stepZ : 0 };

        for (int dxIdx = 0; dxIdx < 2; ++dxIdx) {
            for (int dyIdx = 0; dyIdx < 2; ++dyIdx) {
                for (int dzIdx = 0; dzIdx < 2; ++dzIdx) {
                    int dx = dxs[dxIdx], dy = dys[dyIdx], dz = dzs[dzIdx];
                    if (dx == 0 && dy == 0 && dz == 0) continue;
                    if (contains_block(oldX + dx, oldY + dy, oldZ + dz)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void __fastcall hkSetDirty(uintptr_t chunkRenderer, uintptr_t method) {
    setdirty_o(chunkRenderer, method);

    if (chunkRenderer) {
        uintptr_t chunk = *(uintptr_t*)(chunkRenderer + offsets::ChunkRenderer_chunk);
        if (chunk) {
            fast_raycast::rebuild_chunk(chunk);
        }
    }
}

void rebuild_chunk_safe(int cx, int cy, int cz) {
    fast_raycast::rebuild_chunk_by_pos(cx, cy, cz);
}

void __fastcall hkSetBlockAndRecompute(uintptr_t map, uintptr_t blockData, vec3i* pos, uintptr_t method) {
    setblockandrecompute_o(map, blockData, pos, method);

    if (!pos) return;

    int x = pos->x;
    int y = pos->y;
    int z = pos->z;

    int cx = x >> 4;
    int cy = y >> 4;
    int cz = z >> 4;

    rebuild_chunk_safe(cx, cy, cz);

    int bx = x & 15; // Local X (0-15)
    int by = y & 15; // Local Y
    int bz = z & 15; // Local Z

    if (bx == 0)  rebuild_chunk_safe(cx - 1, cy, cz);
    if (bx == 15) rebuild_chunk_safe(cx + 1, cy, cz);

    if (by == 0)  rebuild_chunk_safe(cx, cy - 1, cz);
    if (by == 15) rebuild_chunk_safe(cx, cy + 1, cz);

    if (bz == 0)  rebuild_chunk_safe(cx, cy, cz - 1);
    if (bz == 15) rebuild_chunk_safe(cx, cy, cz + 1);
}

bool fast_raycast::linecast_chk(const vec3& start, const vec3& end) {
    vec3 dummy;
    return linecast_chk(start, end, dummy);
}

bool fast_raycast::linecast_chk(const vec3& start, const vec3& end, vec3& out_hit) {
    if (start.get_distance(end) > 300.0f) return false; 

    if (contains_block(vec3i((int)start.x, (int)start.y, (int)start.z))) {
        out_hit = start;
        return true;
    }

    vec3 dir = end - start;
    float max_dist = dir.get_magnitude();
    if (max_dist < 0.001f) return false;
    dir = dir.get_normalized();

    const float CELL_SIZE = 16.0f;

    int cx = (int)floor(start.x / CELL_SIZE);
    int cy = (int)floor(start.y / CELL_SIZE);
    int cz = (int)floor(start.z / CELL_SIZE);

    int stepX = (dir.x > 0) ? 1 : -1;
    int stepY = (dir.y > 0) ? 1 : -1;
    int stepZ = (dir.z > 0) ? 1 : -1;

    float tDeltaX = (dir.x != 0) ? fabsf(CELL_SIZE / dir.x) : FLT_MAX;
    float tDeltaY = (dir.y != 0) ? fabsf(CELL_SIZE / dir.y) : FLT_MAX;
    float tDeltaZ = (dir.z != 0) ? fabsf(CELL_SIZE / dir.z) : FLT_MAX;

    float boundary_x = (cx + (stepX > 0 ? 1 : 0)) * CELL_SIZE;
    float boundary_y = (cy + (stepY > 0 ? 1 : 0)) * CELL_SIZE;
    float boundary_z = (cz + (stepZ > 0 ? 1 : 0)) * CELL_SIZE;

    float tMaxX = (dir.x != 0) ? (boundary_x - start.x) / dir.x : FLT_MAX;
    float tMaxY = (dir.y != 0) ? (boundary_y - start.y) / dir.y : FLT_MAX;
    float tMaxZ = (dir.z != 0) ? (boundary_z - start.z) / dir.z : FLT_MAX;

    if (tMaxX < 0) tMaxX = 0;
    if (tMaxY < 0) tMaxY = 0;
    if (tMaxZ < 0) tMaxZ = 0;

    float current_dist = 0.0f;

    while (current_dist <= max_dist) {
        uint64_t key = get_chunk_hash(cx, cy, cz);

        {
            std::shared_lock<std::shared_mutex> lock(cache_mutex);
            auto it = chunk_cache.find(key);

            if (it != chunk_cache.end() && it->second.valid) {
                const auto& chunk = it->second;

                float closest_t = FLT_MAX;
                bool hit_any = false;

                for (const auto& tri : chunk.mesh) {
                    float t;
                    if (intersect_triangle(start, dir, tri, t, max_dist)) {
                        if (t < closest_t) {
                            closest_t = t;
                            hit_any = true;
                        }
                    }
                }

                if (hit_any) {
                    out_hit = start + dir * closest_t;
                    return true;
                }
            }
        }

        if (tMaxX < tMaxY) {
            if (tMaxX < tMaxZ) {
                current_dist = tMaxX;
                tMaxX += tDeltaX;
                cx += stepX;
            }
            else {
                current_dist = tMaxZ;
                tMaxZ += tDeltaZ;
                cz += stepZ;
            }
        }
        else {
            if (tMaxY < tMaxZ) {
                current_dist = tMaxY;
                tMaxY += tDeltaY;
                cy += stepY;
            }
            else {
                current_dist = tMaxZ;
                tMaxZ += tDeltaZ;
                cz += stepZ;
            }
        }
    }

    return false;
}
