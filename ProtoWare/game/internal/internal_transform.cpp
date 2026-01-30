#include "pch.h"
#include "internal_transform.h"

vec3 internal_transform::get_kernel_pos() {
	return access->trsx_array[0].pos;
}
void internal_transform::set_kernel_pos(vec3 pos) {
    access->trsx_array[0].pos = pos;
}
vec3 internal_transform::get_local_pos() {
	return access->trsx_array[access_index].pos;
}
vec3 internal_transform::get_pos(int idx) {
    trsx* trsx_array = access->trsx_array;
    int* parent_array = access->parrent_array;
    int access_idx = idx == -1 ? access_index : idx;

    if (access_idx < 0 || access_idx >= 300) return vec3(0, 0, 0);

    vec3 worldPos = trsx_array[access_idx].pos;
    int index = parent_array[access_idx];
    int max = 0;

    while (index >= 0 && index < 300) {
        if (max++ > 30) break;

        auto& parent = trsx_array[index];

        worldPos = parent.rot * worldPos;
        //worldPos = worldPos * parent.scale;
        worldPos = vec3(worldPos.x * parent.scale.x, worldPos.y * parent.scale.y, worldPos.z * parent.scale.z);
        worldPos = worldPos + parent.pos;

        index = parent_array[index];
    }

    return worldPos;
}
quat internal_transform::get_rot(int idx) {
    trsx* trsx_array = access->trsx_array;
    int* parent_array = access->parrent_array;
    int access_idx = idx == -1 ? access_index : idx;

    if (access_idx < 0 || access_idx >= 300) return vec3(0, 0, 0);

    quat q = trsx_array[access_idx].rot;
    int index = parent_array[access_idx];
    int max = 0;

    while (index >= 0 && index < 300) {
        if (max++ > 30) break;

        auto parent = trsx_array[index].rot;

        q = parent.conjugate() * q;
        q = q.get_normalized();

        index = parent_array[index];
    }

    return q;
}