#include "pch.h"
#include "globals.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline void WeaponSystem__Awake(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x623860))(__this);
}

inline void WeaponSystem__StartEquip(uintptr __this, int _mwid, int _pwid, int _swid, int _a1wid, int _a2wid, int _a3wid, int _g1wid, int _g2wid, int clipammo, int backpack, int clipammo2, int backpack2, int blockammo, int ammo1, int ammo2, int ammo3, int gren1, int gren2, int medkit_w, int medkit_g, int medkit_o, int zbk18m, int zof26, int snaryad, int repair_kit, int tank_light, int tank_medium, int tank_heavy, unsigned char mg, int gp, int flash, int smoke) {
	((void(__fastcall*)(uintptr, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, unsigned char, int, int, int))(GAME_ASSEMBLY_PTR + 0x62e460))(__this, _mwid, _pwid, _swid, _a1wid, _a2wid, _a3wid, _g1wid, _g2wid, clipammo, backpack, clipammo2, backpack2, blockammo, ammo1, ammo2, ammo3, gren1, gren2, medkit_w, medkit_g, medkit_o, zbk18m, zof26, snaryad, repair_kit, tank_light, tank_medium, tank_heavy, mg, gp, flash, smoke);
}

inline void WeaponSystem__StartEquip(uintptr __this, int _pwid, int clipammo, int backpack) {
	((void(__fastcall*)(uintptr, int, int, int))(GAME_ASSEMBLY_PTR + 0x62ea60))(__this, _pwid, clipammo, backpack);
}

inline void WeaponSystem__FixedUpdate(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624350))(__this);
}

inline bool WeaponSystem__OnWeaponAttack(uintptr __this, uintptr weaponshooter) {
	return ((bool(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x626330))(__this, weaponshooter);
}

inline void WeaponSystem__OnWeaponSelect(uintptr __this, uintptr weapon) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x62ca40))(__this, weapon);
}

inline void WeaponSystem__UseVehicleModul(uintptr __this, uintptr AS, int module_index) {
	((void(__fastcall*)(uintptr, uintptr, int))(GAME_ASSEMBLY_PTR + 0x62f070))(__this, AS, module_index);
}

inline bool WeaponSystem__TankFire(uintptr __this, int sid, uintptr FP) {
	return ((bool(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x62ec50))(__this, sid, FP);
}

inline void WeaponSystem__TankMGFire(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x62f010))(__this);
}

inline void WeaponSystem__JeepMGFire(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x626250))(__this);
}

inline bool WeaponSystem__OnWeaponReloadStart(uintptr __this, uintptr weapon) {
	return ((bool(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x62c740))(__this, weapon);
}

inline void WeaponSystem__OnWeaponReloadEnd(uintptr __this, uintptr weapon) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x62c310))(__this, weapon);
}

inline void WeaponSystem__OnWeaponZoomStart(uintptr __this, uintptr weapon) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x62db90))(__this, weapon);
}

inline bool WeaponSystem__HasScope(uintptr __this, int WeaponID) {
	return ((bool(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x6260c0))(__this, WeaponID);
}

inline void WeaponSystem__OnWeaponZoomEnd(uintptr __this, uintptr weapon) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x62daf0))(__this, weapon);
}

inline bool WeaponSystem__WeaponCanReload(uintptr __this, int wid) {
	return ((bool(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x62f370))(__this, wid);
}

inline void WeaponSystem__HideWeapons(uintptr __this, bool val) {
	((void(__fastcall*)(uintptr, bool))(GAME_ASSEMBLY_PTR + 0x626230))(__this, val);
}

inline bool WeaponSystem__OnWeaponMeleeAttack(uintptr __this, uintptr weapon) {
	return ((bool(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x628650))(__this, weapon);
}

inline void WeaponSystem__SetPrimaryWeapon(uintptr __this, bool build_mode_and_block) {
	((void(__fastcall*)(uintptr, bool))(GAME_ASSEMBLY_PTR + 0x62e1a0))(__this, build_mode_and_block);
}

inline void WeaponSystem__alter_weapon_raycast(uintptr __this, int wid, uintptr WS) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x62f480))(__this, wid, WS);
}

inline uintptr WeaponSystem__GetCursor(uintptr __this, bool inside, int radius) {
	return ((uintptr(__fastcall*)(uintptr, bool, int))(GAME_ASSEMBLY_PTR + 0x625b60))(__this, inside, radius);
}

inline uintptr WeaponSystem__GetCursorUnderRay(uintptr vec, uintptr __this, bool inside, int radius, uintptr ray) {
	return ((uintptr(__fastcall*)(uintptr, uintptr, bool, int, uintptr))(GAME_ASSEMBLY_PTR + 0x625930))(vec, __this, inside, radius, ray);
}

inline void WeaponSystem__weapon_attack_block(uintptr __this, int wid, uintptr pointvalue, float x1, float y1, float z1, float x2, float y2, float z2, bool alter_damage) {
	((void(__fastcall*)(uintptr, int, uintptr, float, float, float, float, float, float, bool))(GAME_ASSEMBLY_PTR + 0x630010))(__this, wid, pointvalue, x1, y1, z1, x2, y2, z2, alter_damage);
}

inline bool WeaponSystem__isPrimaryWeapon(uintptr __this, int wid) {
	return ((bool(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x62ff20))(__this, wid);
}

inline int WeaponSystem__GetAmmoWid(uintptr __this, int i) {
	return ((int(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x624e60))(__this, i);
}

inline int WeaponSystem__GetGAmmo(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e30))(__this);
}

inline int WeaponSystem__GetHAmmo(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e40))(__this);
}

inline int WeaponSystem__GetAmmo(uintptr __this, int i) {
	return ((int(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x624e90))(__this, i);
}

inline int WeaponSystem__GetPrimaryAmmo(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625ec0))(__this);
}

inline int WeaponSystem__GetSecondaryAmmo(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625ed0))(__this);
}

inline int WeaponSystem__GetAmmoGP(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624b10))(__this);
}

inline int WeaponSystem__GetAmmoMedkit_w(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624c30))(__this);
}

inline int WeaponSystem__GetAmmoMedkit_g(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624c10))(__this);
}

inline int WeaponSystem__GetAmmoMedkit_o(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624c20))(__this);
}

inline int WeaponSystem__GetModuleRepairKit(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625ea0))(__this);
}

inline int WeaponSystem__GetModuleFlash(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e90))(__this);
}

inline int WeaponSystem__GetModuleSmoke(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625eb0))(__this);
}

inline int WeaponSystem__GetJeepMGAmmo(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e50))(__this);
}

inline int WeaponSystem__GetMGAmmo(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e80))(__this);
}

inline int WeaponSystem__GetMGAmmoClip(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e70))(__this);
}

inline int WeaponSystem__GetMGAmmoBackpack(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625e60))(__this);
}

inline void WeaponSystem__weapon_raycast(uintptr __this, int wid, float dist, int blockdist, uintptr WS) {
	((void(__fastcall*)(uintptr, int, float, int, uintptr))(GAME_ASSEMBLY_PTR + 0x630810))(__this, wid, dist, blockdist, WS);
}

inline int WeaponSystem__GetZBK18M(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625f80))(__this);
}

inline int WeaponSystem__GetZOF26(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x626020))(__this);
}

inline int WeaponSystem__GetSnaryad(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x625ee0))(__this);
}

inline void WeaponSystem__SetZombieWeapon(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x62e1c0))(__this);
}

inline void WeaponSystem__SetAnimalWeapon(uintptr __this, int _wID) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x62e150))(__this, _wID);
}

inline bool WeaponSystem__GetBlackSkin(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624f60))(__this);
}

inline void WeaponSystem__Shake(uintptr __this, UNITYENGINE_VECTOR3 epos, bool force) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, bool))(GAME_ASSEMBLY_PTR + 0x62e270))(__this, epos, force);
}

inline void WeaponSystem__SetMouseSensitivity(uintptr __this, float val) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x62e180))(__this, val);
}

inline void WeaponSystem__StartShake(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x62ebd0))(__this);
}

inline void WeaponSystem__LiftMeUp(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x626270))(__this);
}

inline uintptr WeaponSystem__ShakeLift(uintptr __this, float timer) {
	return ((uintptr(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x62e1f0))(__this, timer);
}

inline int WeaponSystem__GetAmmoRPG7(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624d00))(__this);
}

inline int WeaponSystem__GetAmmoMinefly(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624c40))(__this);
}

inline int WeaponSystem__GetAmmoJavelin(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624b50))(__this);
}

inline int WeaponSystem__GetAmmoRPGClip(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624dc0))(__this);
}

inline void WeaponSystem__TankMGReload(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x62f050))(__this);
}

inline void WeaponSystem__DetonateMyC4(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x624220))(__this);
}

inline void WeaponSystem__ctor(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x62f450))(__this);
}
