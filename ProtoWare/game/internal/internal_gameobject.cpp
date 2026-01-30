#include "pch.h"
#include "globals.h"
#include "internal_gameobject.h"
#include "internal_component.h"
#include "il2cpp_structs.h"
#include "component.h"

internal_transform* internal_gameobject::get_transform() {
	__int64 v3; // rax
	__int64 v4; // r8
	uintptr v29;

	v3 = list_start;
	if (!v3) return 0;
	v4 = v3 + 16i64 * list_count;
	if (v3 == v4)
		return 0;

	int range_start = *(int*)(unityplayer + 0x1A6CF70 + 48);
	unsigned int range_size = *(int*)(unityplayer + 0x1A6CF70 + 52);

	int maxx = 0;
	while (*(int*)v3 - range_start >= range_size)
	{
		if (maxx > 1000) return 0;
		maxx++;
		v3 += 16i64;
		if (v3 == v4) {
			return 0;
		}
	};
	return *(internal_transform**)(v3 + 8);
}
component* internal_gameobject::get_component(const char* name) {
	int component_count = list_count;
	uintptr component_list = list_start;
	for (int i = 0; i < component_count; i++) {
		uintptr comp = *(uintptr*)(component_list + (i * 16) + 8);
		if (!comp) continue;
		component* extcomp = *(component**)(comp + 0x28);
		if (!extcomp || !extcomp->il2cpp_class || !extcomp->il2cpp_class->name) continue;
		const char* cname = extcomp->il2cpp_class->name;
		if (strcmp(cname, name) == 0) {
			return extcomp;
		}
	}
	return 0;
}
internal_component* internal_gameobject::get_component_interned(const char* name) {
	int component_count = *(int*)((uintptr)this + 64);
	uintptr component_list = *(uintptr*)((uintptr)this + 48);
	for (int i = 0; i < component_count; i++) {
		uintptr comp = *(uintptr*)(component_list + (i * 16) + 8);
		component* extcomp = *(component**)(comp + 0x28);
		const char* cname = extcomp->il2cpp_class->name;
		if (strcmp(cname, name) == 0) {
			return (internal_component*)comp;
		}
	}
	return 0;
}