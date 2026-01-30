#include "pch.h"
#include "il2cpp_structs.h"
#include "math3d.h"

#define IL2CPP_CLASS il2cpp_class*
#define UNITYENGINE_VECTOR2 vec2
#define UNITYENGINE_VECTOR3 vec3
#define UNITYENGINE_VECTOR4 quat
#define UNITYENGINE_QUATERNION quat

struct vp_Shooter {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	char padding_0[136];
	uintptr m_CharacterController; // 0x98
	uintptr m_OperatorTransform; // 0xa0
	uintptr m_FPSWeapon; // 0xa8
	uintptr ProjectilePrefab; // 0xb0
	float ProjectileScale; // 0xb8
	float ProjectileFiringRate; // 0xbc
	float ProjectileROF; // 0xc0
	float ProjectileSpawnDelay; // 0xc4
	int ProjectileCount; // 0xc8
	float ProjectileSpread; // 0xcc
	float m_NextAllowedFireTime; // 0xd0
	bool secondFire; // 0xd4
	char padding_1[3];
	int currentFiringWeaponID; // 0xd8
	float flameFiringTimer; // 0xdc
	UNITYENGINE_VECTOR3 MuzzleFlashPosition; // 0xe0
	UNITYENGINE_VECTOR3 MuzzleFlashScale; // 0xec
	float MuzzleFlashFadeSpeed; // 0xf8
	char padding_2[4];
	uintptr MuzzleFlashPrefab; // 0x100
	float MuzzleFlashDelay; // 0x108
	char padding_3[4];
	uintptr m_MuzzleFlash; // 0x110
	uintptr MuzzleFlashTransformPosition; // 0x118
	uintptr ShellTransformPosition; // 0x120
	uintptr ShellPrefab; // 0x128
	float ShellScale; // 0x130
	UNITYENGINE_VECTOR3 ShellEjectDirection; // 0x134
	UNITYENGINE_VECTOR3 ShellEjectPosition; // 0x140
	float ShellEjectVelocity; // 0x14c
	float ShellEjectDelay; // 0x150
	float ShellEjectSpin; // 0x154
	uintptr SoundFire; // 0x158
	float SoundFireDelay; // 0x160
	UNITYENGINE_VECTOR2 SoundFirePitch; // 0x164
	bool specialAttack; // 0x16c
	char padding_4[3];
	uintptr m_Player; // 0x170
};