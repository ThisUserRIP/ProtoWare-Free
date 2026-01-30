#include "pch.h"
#include "il2cpp_structs.h"

#define IL2CPP_CLASS il2cpp_class*

struct Ammo {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	uintptr ammo_block; // 0x18
	uintptr ammo_shotgun; // 0x20
	uintptr ammo_machinegun; // 0x28
	uintptr ammo_rifle; // 0x30
	uintptr ammo_m61; // 0x38
	uintptr ammo_shmel; // 0x40
	uintptr ammo_medkit; // 0x48
	uintptr ammo_tnt; // 0x50
	uintptr ammo_gp; // 0x58
	uintptr ammo_rpg; // 0x60
	uintptr ammo_zbk18m; // 0x68
	uintptr ammo_zof26; // 0x70
	uintptr ammo_snaryad; // 0x78
	uintptr ammo_repair_kit; // 0x80
	uintptr ammo_arrows; // 0x88
	uintptr ammo_flamethrower; // 0x90
	uintptr ammo_gp_hud; // 0x98
	uintptr ammo_javelin_hud; // 0xa0
	uintptr ammo_minefly_hud; // 0xa8
	uintptr ammo_rpg_hud; // 0xb0
	uintptr ammo_shmel_hud; // 0xb8
	uintptr ammo_snowball_hud; // 0xc0
	uintptr r_ammo_gun; // 0xc8
	char padding_0[8];
	uintptr r_ammo_m61; // 0xd8
	char padding_1[8];
	uintptr r_ammo_shmel; // 0xe8
	char padding_2[8];
	uintptr r_ammo_tnt; // 0xf8
	char padding_3[8];
	uintptr r_ammo_gp; // 0x108
	char padding_4[8];
	uintptr r_ammo_rpg; // 0x118
	char padding_5[8];
	uintptr r_ammo_zbk18m; // 0x128
	char padding_6[8];
	uintptr r_ammo_zof26; // 0x138
	char padding_7[8];
	uintptr r_ammo_snaryad; // 0x148
	char padding_8[8];
	uintptr r_ammo_repair_kit; // 0x158
	char padding_9[8];
	uintptr r_ammo_snowball; // 0x168
	char padding_a[8];
	int weaponid; // 0x178
	int clip; // 0x17c
	int backpack; // 0x180
	int g1count; // 0x184
	int g2count; // 0x188
	int a1count; // 0x18c
	int a2count; // 0x190
	int a3count; // 0x194
	int gp; // 0x198
	int zbk18m; // 0x19c
	int zof26; // 0x1a0
	int snaryad; // 0x1a4
	int repair_kit; // 0x1a8
	char padding_b[4];
	uintptr gui_style; // 0x1b0
	bool draw; // 0x1b8
	bool initialized; // 0x1b9
};