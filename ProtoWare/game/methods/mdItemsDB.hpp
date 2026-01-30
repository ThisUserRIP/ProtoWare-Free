#include "pch.h"
#include "globals.h"

#define GAME_ASSEMBLY_PTR gameassembly


inline bool ItemsDB__CheckItem(int ID) {
	return ((bool(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0xa08090))(ID);
}

inline uintptr ItemsDB__GetItemData(int id) {
	return ((uintptr(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0xa08100))(id);
}

inline void ItemsDB__LoadMissingIcons() {
	((void(__fastcall*)())(GAME_ASSEMBLY_PTR + 0xa08260))();
}

inline int ItemsDB__GetItemIDByPurchaseID(int _purchaseID) {
	return ((int(__fastcall*)(int))(GAME_ASSEMBLY_PTR + 0xa08190))(_purchaseID);
}

inline void ItemsDB__ctor(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x4342a0))(__this);
}
