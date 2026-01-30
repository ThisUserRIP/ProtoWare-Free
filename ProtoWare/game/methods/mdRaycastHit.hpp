#include "pch.h"
#include "globals.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline uintptr RaycastHit__get_collider(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2934aa0))(__this);
}

inline UNITYENGINE_VECTOR3 RaycastHit__get_point(uintptr __this) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x286e770))(__this);
}

inline void RaycastHit__set_point(uintptr __this, UNITYENGINE_VECTOR3 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x25cea20))(__this, value);
}

inline UNITYENGINE_VECTOR3 RaycastHit__get_normal(uintptr __this) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888530))(__this);
}

inline void RaycastHit__set_normal(uintptr __this, UNITYENGINE_VECTOR3 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2888770))(__this, value);
}

inline void RaycastHit__set_barycentricCoordinate(uintptr __this, UNITYENGINE_VECTOR3 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2934cd0))(__this, value);
}

inline float RaycastHit__get_distance(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x29288f0))(__this);
}

inline void RaycastHit__set_distance(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x468290))(__this, value);
}

inline uintptr RaycastHit__get_transform(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2934bf0))(__this);
}

inline uintptr RaycastHit__get_rigidbody(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2934b40))(__this);
}
