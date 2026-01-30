#include "pch.h"
#include "globals.h"

#define GAME_ASSEMBLY_PTR gameassembly


inline void ObscuredInt__ctor(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x5aeed0))(__this);
}

inline void ObscuredInt__ctor(uintptr __this, int value) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x5aef00))(__this, value);
}

inline int ObscuredInt__get_value(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x5aef40))(__this);
}

inline void ObscuredInt__set_value(uintptr __this, int value) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x5aef50))(__this, value);
}
