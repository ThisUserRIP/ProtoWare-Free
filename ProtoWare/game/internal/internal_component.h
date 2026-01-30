#pragma once
struct internal_gameobject;
struct component;

struct internal_component {
public:
	char padding[40];
	component* default_component;
	internal_gameobject* gameobject;
};

