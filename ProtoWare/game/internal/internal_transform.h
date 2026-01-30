#pragma once
#include "pch.h"
#include "math3d.h"
struct trsx {
	vec3 pos;
	int padding1;
	quat rot;
	vec3 scale;
	int padding2;
};

struct transform_access {
	char padding1[24];
	trsx* trsx_array;
	int* parrent_array;
};

struct internal_gameobject;
struct component;

struct internal_transform {
public:
	char padding1[40];
	component* default_component;
	internal_gameobject* go;
	transform_access* access;
	int access_index;

	vec3 get_kernel_pos();
	void set_kernel_pos(vec3 pos);
	vec3 get_local_pos();
	vec3 get_pos(int access_idx = -1);
	quat get_rot(int access_idx = -1);

	//vec3 get_forward() { return get_rot().get_forward(); }
	//vec3 get_up() { return get_rot().get_up(); }
};

