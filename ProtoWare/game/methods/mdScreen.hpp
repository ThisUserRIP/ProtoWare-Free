#include "pch.h"
#include "globals.h"
#include "tarray.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define IL2CPP_ARRAY tarray*


inline int Screen__get_width() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5cf0))();
}

inline int Screen__get_height() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5c90))();
}

inline float Screen__get_dpi() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5c00))();
}

inline void Screen__RequestOrientation(int orient) {
	((void(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x28a5a10))(orient);
}

inline uintptr Screen__GetScreenOrientation() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a59e0))();
}

inline uintptr Screen__get_orientation() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a59e0))();
}

inline void Screen__set_orientation(int value) {
	((void(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0x28a5d60))(value);
}

inline uintptr Screen__get_currentResolution() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5bc0))();
}

inline bool Screen__get_fullScreen() {
	return ((bool(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5c60))();
}

inline void Screen__set_fullScreen(bool value) {
	((void(__fastcall*)(bool))(GAME_ASSEMBLY_PTR + 0x28a5d20))(value);
}

inline uintptr Screen__get_fullScreenMode() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5c30))();
}

inline void Screen__SetResolution(int width, int height, int fullscreenMode, int preferredRefreshRate) {
	((void(__fastcall*)(int, int, int, int))(GAME_ASSEMBLY_PTR + 0x28a5a50))(width, height, fullscreenMode, preferredRefreshRate);
}

inline void Screen__SetResolution(int width, int height, bool fullscreen, int preferredRefreshRate) {
	((void(__fastcall*)(int, int, bool, int))(GAME_ASSEMBLY_PTR + 0x28a5b10))(width, height, fullscreen, preferredRefreshRate);
}

inline void Screen__SetResolution(int width, int height, bool fullscreen) {
	((void(__fastcall*)(int, int, bool))(GAME_ASSEMBLY_PTR + 0x28a5ab0))(width, height, fullscreen);
}

inline IL2CPP_ARRAY Screen__get_resolutions() {
	return ((IL2CPP_ARRAY(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28a5cc0))();
}

inline void Screen__get_currentResolution_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28a5b80))(ret);
}
