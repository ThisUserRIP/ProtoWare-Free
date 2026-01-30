#pragma once
struct internal_transform;
struct internal_component;
struct component;

struct internal_gameobject {
public:
	char padding1[48];
	uintptr list_start;
	uintptr padding2;
	uintptr list_count;
	char padding3[24];
	char* name;

	internal_transform* get_transform();
	component* get_component(const char* name);
	internal_component* get_component_interned(const char* name);
};

