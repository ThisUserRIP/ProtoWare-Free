#include "pch.h"
#include "il2cpp_structs.h"
#include "tarray.h"

#define IL2CPP_CLASS il2cpp_class*
#define IL2CPP_ARRAY tarray*

struct WeaponSystem {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	float m_NextAllowedFireTimeOwerride; // 0x18
	char padding_0[4]; 
	uintptr m_Input; // 0x20
	uintptr m_FPCamera; // 0x28
	uintptr myDummy; // 0x30
	uintptr cscl; // 0x38
	uintptr cscr; // 0x40
	uintptr csmap; // 0x48
	uintptr cspm; // 0x50
	uintptr csig; // 0x58
	uintptr csam; // 0x60
	uintptr csrm; // 0x68
	uintptr cspc; // 0x70
	uintptr cscc; // 0x78
	uintptr m_Health; // 0x80
	uintptr cssw; // 0x88
	int LM; // 0x90
	int mwid; // 0x94
	int pwid; // 0x98
	int swid; // 0x9c
	IL2CPP_ARRAY ammowid; // 0xa0, Int32[]
	IL2CPP_ARRAY ammocount; // 0xa8, Int32[]
	int g1wid; // 0xb0
	int g2wid; // 0xb4
	int gren1count; // 0xb8
	int gren2count; // 0xbc
	int ammo_clip; // 0xc0
	int ammo_fullclip; // 0xc4
	int ammo_backpack; // 0xc8
	int ammo_clip2; // 0xcc
	int ammo_fullclip2; // 0xd0
	int ammo_backpack2; // 0xd4
	int ammo_block; // 0xd8
	int ammo_medkit_w; // 0xdc
	int ammo_medkit_g; // 0xe0
	int ammo_medkit_o; // 0xe4
	int ammo_gp; // 0xe8
	int ammo_clip_rockets; // 0xec
	int ammo_zbk18m; // 0xf0
	int ammo_zof26; // 0xf4
	int ammo_snaryad; // 0xf8
	int ammo_repair_kit; // 0xfc
	int ammo_module_flash; // 0x100
	int ammo_module_smoke; // 0x104
	int ammo_tank_light; // 0x108
	int ammo_tank_heavy; // 0x10c
	int MGammo_clip; // 0x110
	int MGammo; // 0x114
	int JeepMGammo; // 0x118
	int MGammo_backpack; // 0x11c
	int CURRENT_WEAPON_ID; // 0x120
	unsigned char MGitem; // 0x124
	char padding_1[3]; 
	uintptr goBlockSetup; // 0x128
	uintptr goBlockCrash; // 0x130
	uintptr goBlockTNT; // 0x138
	float clientreload2; // 0x140
	bool targetLock; // 0x144
	char padding_2[3]; 
	uintptr target; // 0x148
	uintptr lastTarget; // 0x150
	bool targetLocked; // 0x158
	char padding_3[7]; 
	uintptr _S; // 0x160
	uintptr _AS; // 0x168
	uintptr MG; // 0x170
	int layerMask; // 0x178
	int ZlayerMask; // 0x17c
	bool specialAttack; // 0x180
};