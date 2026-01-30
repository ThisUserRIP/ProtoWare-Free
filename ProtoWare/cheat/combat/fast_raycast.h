#pragma once
#include "math3d.h"
#include <vector>

struct Triangle {
	vec3 v0, v1, v2;
};

struct CachedChunk {
	vec3i position; 
	vec3 min_world, max_world; 
	std::vector<Triangle> mesh;
	bool valid = false;
};

namespace fast_raycast {
	
	void initialize();
	void update();

	void rebuild_all();
	void rebuild_chunk(uintptr_t chunk_ptr);
	void rebuild_chunk_by_pos(int x, int y, int z);
	void clear_cache();

	bool contains_block(vec3i block);
	bool contains_block(vec3 block);
	bool contains_block(int x, int y, int z);

	bool slow_raycast(vec3 start, vec3 end, int layermask);
	bool linecast(const vec3& start, const vec3& end);
	bool linecast_chk(const vec3& start, const vec3& end);
	bool linecast_chk(const vec3& start, const vec3& end, vec3& out_hit);
};

