#include "pch.h"
#include "globals.h"
#include "monostring.h"
#include "tarray.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define IL2CPP_STRING monostring*
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline bool Input__GetKeyInt(int key) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926810))(key);
}

inline bool Input__GetKeyUpInt(int key) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926850))(key);
}

inline bool Input__GetKeyDownInt(int key) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x29267d0))(key);
}

inline float Input__GetAxis(IL2CPP_STRING axisName) {
	return ((float(__fastcall*)(IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x29266a0))(axisName);
}

inline float Input__GetAxisRaw(IL2CPP_STRING axisName) {
	return ((float(__fastcall*)(IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x2926660))(axisName);
}

inline bool Input__GetButton(IL2CPP_STRING buttonName) {
	return ((bool(__fastcall*)(IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x2926760))(buttonName);
}

inline bool Input__GetButtonDown(IL2CPP_STRING buttonName) {
	return ((bool(__fastcall*)(IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x29266e0))(buttonName);
}

inline bool Input__GetButtonUp(IL2CPP_STRING buttonName) {
	return ((bool(__fastcall*)(IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x2926720))(buttonName);
}

inline bool Input__GetMouseButton(int button) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926910))(button);
}

inline bool Input__GetMouseButtonDown(int button) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926890))(button);
}

inline bool Input__GetMouseButtonUp(int button) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x29268d0))(button);
}

inline IL2CPP_ARRAY Input__GetJoystickNames() {
	return ((IL2CPP_ARRAY(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x29267a0))();
}

inline uintptr Input__GetTouch(int index) {
	return ((uintptr(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926990))(index);
}

inline bool Input__GetKey(int key) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926810))(key);
}

inline bool Input__GetKeyUp(int key) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926850))(key);
}

inline bool Input__GetKeyDown(int key) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x29267d0))(key);
}

inline bool Input__get_simulateMouseWithTouches() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926ce0))();
}

inline void Input__set_simulateMouseWithTouches(bool value) {
	((void(__fastcall*)(bool))(GAME_ASSEMBLY_PTR + 0x2926ff0))(value);
}

inline bool Input__get_anyKey() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926a70))();
}

inline UNITYENGINE_VECTOR3 Input__get_mousePosition() {
	return ((UNITYENGINE_VECTOR3(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926bc0))();
}

inline UNITYENGINE_VECTOR2 Input__get_mouseScrollDelta() {
	return ((UNITYENGINE_VECTOR2(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926c70))();
}

inline uintptr Input__get_imeCompositionMode() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926b50))();
}

inline void Input__set_imeCompositionMode(int value) {
	((void(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x2926f70))(value);
}

inline IL2CPP_STRING Input__get_compositionString() {
	return ((IL2CPP_STRING(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926b20))();
}

inline UNITYENGINE_VECTOR2 Input__get_compositionCursorPos() {
	return ((UNITYENGINE_VECTOR2(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926ae0))();
}

inline void Input__set_compositionCursorPos(UNITYENGINE_VECTOR2 value) {
	((void(__fastcall*)(UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x2926f30))(value);
}

inline bool Input__get_mousePresent() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926c00))();
}

inline int Input__get_touchCount() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926d10))();
}

inline bool Input__get_touchPressureSupported() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926d40))();
}

inline bool Input__get_touchSupported() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926d70))();
}

inline bool Input__get_multiTouchEnabled() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926cb0))();
}

inline void Input__set_multiTouchEnabled(bool value) {
	((void(__fastcall*)(bool))(GAME_ASSEMBLY_PTR + 0x2926fb0))(value);
}

inline UNITYENGINE_VECTOR3 Input__get_acceleration() {
	return ((UNITYENGINE_VECTOR3(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926a30))();
}

inline IL2CPP_ARRAY Input__get_touches() {
	return ((IL2CPP_ARRAY(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926da0))();
}

inline bool Input__CheckDisabled() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2926630))();
}

inline void Input__GetTouch_Injected(int index, uintptr ret) {
	((void(__fastcall*)(int, uintptr))(GAME_ASSEMBLY_PTR + 0x2926950))(index, ret);
}

inline void Input__get_mousePosition_Injected(UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2926b80))(ret);
}

inline void Input__get_mouseScrollDelta_Injected(UNITYENGINE_VECTOR2 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x2926c30))(ret);
}

inline void Input__get_compositionCursorPos_Injected(UNITYENGINE_VECTOR2 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x2926aa0))(ret);
}

inline void Input__set_compositionCursorPos_Injected(UNITYENGINE_VECTOR2 value) {
	((void(__fastcall*)(UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x2926ef0))(value);
}

inline void Input__get_acceleration_Injected(UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x29269f0))(ret);
}
