#pragma once
#include "math3d.h"
struct internal_gameobject;
struct internal_camera {
public:
	char padding1[48];
	internal_gameobject* go;
	char padding2[36];
	matrix4x4 viewmatrix;
	matrix4x4 projmatrix;
};

