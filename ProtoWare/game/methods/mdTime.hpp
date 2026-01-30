#include "pch.h"
#include "globals.h"

#define GAME_ASSEMBLY_PTR gameassembly


inline float Time__get_time() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9b60))();
}

inline float Time__get_timeSinceLevelLoad() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9b30))();
}

inline float Time__get_deltaTime() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d99b0))();
}

inline float Time__get_unscaledTime() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9bc0))();
}

inline float Time__get_fixedUnscaledTime() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9a10))();
}

inline float Time__get_unscaledDeltaTime() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9b90))();
}

inline float Time__get_fixedDeltaTime() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d99e0))();
}

inline void Time__set_fixedDeltaTime(float value) {
	((void(__fastcall*)(float))(GAME_ASSEMBLY_PTR + 0x28d9bf0))(value);
}

inline float Time__get_smoothDeltaTime() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9ad0))();
}

inline float Time__get_timeScale() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9b00))();
}

inline void Time__set_timeScale(float value) {
	((void(__fastcall*)(float))(GAME_ASSEMBLY_PTR + 0x28d9c30))(value);
}

inline int Time__get_frameCount() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9a40))();
}

inline int Time__get_renderedFrameCount() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9aa0))();
}

inline float Time__get_realtimeSinceStartup() {
	return ((float(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x28d9a70))();
}
