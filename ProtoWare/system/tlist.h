#pragma once
#include "pch.h"
#include "tarray.h"

struct tlist {
public:
	uintptr dummy1;
	uintptr dummy2;
	tarray* array;
	int size;
};

