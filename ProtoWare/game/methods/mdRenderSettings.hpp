#include "pch.h"
#include "globals.h"

#define GAME_ASSEMBLY_PTR gameassembly


inline bool RenderSettings__get_fog() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0c70))();
}

inline float RenderSettings__get_fogStartDistance() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0c40))();
}

inline void RenderSettings__set_fogStartDistance(float value) {
	((void(__fastcall*)(float))(GAME_ASSEMBLY_PTR + 0x28a1030))(value);
}

inline float RenderSettings__get_fogEndDistance() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0be0))();
}

inline void RenderSettings__set_fogEndDistance(float value) {
	((void(__fastcall*)(float))(GAME_ASSEMBLY_PTR + 0x28a0ff0))(value);
}

inline uintptr RenderSettings__get_fogMode() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0c10))();
}

inline uintptr RenderSettings__get_fogColor() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0b70))();
}

inline void RenderSettings__set_fogColor(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0fb0))(value);
}

inline float RenderSettings__get_fogDensity() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0bb0))();
}

inline uintptr RenderSettings__get_ambientMode() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a09e0))();
}

inline void RenderSettings__set_ambientMode(int value) {
	((void(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x28a0eb0))(value);
}

inline uintptr RenderSettings__get_ambientSkyColor() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0af0))();
}

inline void RenderSettings__set_ambientSkyColor(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0f30))(value);
}

inline uintptr RenderSettings__get_ambientEquatorColor() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0920))();
}

inline void RenderSettings__set_ambientEquatorColor(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0df0))(value);
}

inline uintptr RenderSettings__get_ambientGroundColor() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a09a0))();
}

inline void RenderSettings__set_ambientGroundColor(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0e70))(value);
}

inline uintptr RenderSettings__get_subtractiveShadowColor() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0d40))();
}

inline uintptr RenderSettings__get_skybox() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0cd0))();
}

inline void RenderSettings__set_skybox(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a1070))(value);
}

inline uintptr RenderSettings__get_sun() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0d80))();
}

inline void RenderSettings__set_sun(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a10b0))(value);
}

inline uintptr RenderSettings__get_ambientProbe() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0a50))();
}

inline float RenderSettings__get_reflectionIntensity() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a0ca0))();
}

inline void RenderSettings__get_fogColor_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0b30))(ret);
}

inline void RenderSettings__set_fogColor_Injected(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0f70))(value);
}

inline void RenderSettings__get_ambientSkyColor_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0ab0))(ret);
}

inline void RenderSettings__set_ambientSkyColor_Injected(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0ef0))(value);
}

inline void RenderSettings__get_ambientEquatorColor_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a08e0))(ret);
}

inline void RenderSettings__set_ambientEquatorColor_Injected(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0db0))(value);
}

inline void RenderSettings__get_ambientGroundColor_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0960))(ret);
}

inline void RenderSettings__set_ambientGroundColor_Injected(uintptr value) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0e30))(value);
}

inline void RenderSettings__get_subtractiveShadowColor_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0d00))(ret);
}

inline void RenderSettings__get_ambientProbe_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a0a10))(ret);
}
