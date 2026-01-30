#pragma once
#include "pch.h"
struct tarray {
public:
	uintptr dummy1; // 0x0
	uintptr dummy2; // 0x8
	uintptr array_bounds; // 0x10
	int max_size; // 0x18
	int padding1;
	uintptr array; // 0x20

	uintptr element(int idx, int padding = 8) {
		if (idx >= max_size) return 0;
		return *(uintptr*)((uintptr)&array + (idx * padding));
	}
};

