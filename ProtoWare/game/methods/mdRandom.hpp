#include "pch.h"
#include "globals.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline void Random__InitState(int seed) {
	((void(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x28b5950))(seed);
}

inline uintptr Random__get_state() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b5c20))();
}

inline void Random__set_state(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28b5cd0))(value);
}

inline float Random__Range(float minInclusive, float maxInclusive) {
	return ((float(__fastcall*)(float, float))(GAME_ASSEMBLY_PTR + 0x28b59d0))(minInclusive, maxInclusive);
}

inline int Random__Range(int minInclusive, int maxExclusive) {
	return ((int(__fastcall*)(int, int))(GAME_ASSEMBLY_PTR + 0x28b5990))(minInclusive, maxExclusive);
}

inline int Random__RandomRangeInt(int minInclusive, int maxExclusive) {
	return ((int(__fastcall*)(int, int))(GAME_ASSEMBLY_PTR + 0x28b5990))(minInclusive, maxExclusive);
}

inline float Random__get_value() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b5c60))();
}

inline UNITYENGINE_VECTOR3 Random__get_insideUnitSphere() {
	return ((UNITYENGINE_VECTOR3(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b5aa0))();
}

inline void Random__GetRandomUnitCircle(UNITYENGINE_VECTOR2 output) {
	((void(__fastcall*)(UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x28b5910))(output);
}

inline UNITYENGINE_VECTOR2 Random__get_insideUnitCircle() {
	return ((UNITYENGINE_VECTOR2(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b5a20))();
}

inline UNITYENGINE_VECTOR3 Random__get_onUnitSphere() {
	return ((UNITYENGINE_VECTOR3(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b5b20))();
}

inline UNITYENGINE_QUATERNION Random__get_rotation() {
	return ((UNITYENGINE_QUATERNION(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b5ba0))();
}

inline uintptr Random__ColorHSV() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28b58b0))();
}

inline uintptr Random__ColorHSV(float hueMin, float hueMax, float saturationMin, float saturationMax, float valueMin, float valueMax, float alphaMin, float alphaMax) {
	return ((uintptr(__fastcall*)(float, float, float, float, float, float, float, float))(GAME_ASSEMBLY_PTR + 0x28b56d0))(hueMin, hueMax, saturationMin, saturationMax, valueMin, valueMax, alphaMin, alphaMax);
}

inline void Random__get_state_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28b5be0))(ret);
}

inline void Random__set_state_Injected(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28b5c90))(value);
}

inline void Random__get_insideUnitSphere_Injected(UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x28b5a60))(ret);
}

inline void Random__get_onUnitSphere_Injected(UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x28b5ae0))(ret);
}

inline void Random__get_rotation_Injected(UNITYENGINE_QUATERNION ret) {
	((void(__fastcall*)(UNITYENGINE_QUATERNION))(GAME_ASSEMBLY_PTR + 0x28b5b60))(ret);
}
