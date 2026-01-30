#include "pch.h"
#include "il2cpp_structs.h"
#include "monostring.h"
#include "tarray.h"
#include "math3d.h"

#define IL2CPP_CLASS il2cpp_class*
#define IL2CPP_STRING monostring*
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2
#define UNITYENGINE_VECTOR3 vec3
#define UNITYENGINE_VECTOR4 quat
#define UNITYENGINE_QUATERNION quat

struct ServerBotData {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	IL2CPP_ARRAY Item; // 0x10, Int32[]
	UNITYENGINE_VECTOR3 position; // 0x18
	UNITYENGINE_VECTOR3 rotation; // 0x24
	unsigned char Dead; // 0x30
	char padding_0[3];
	int Helmet; // 0x34
	int HelmetHealth; // 0x38
	int Skin; // 0x3c
	int Ha1; // 0x40
	int Ha2; // 0x44
	int Ha3; // 0x48
	int Znak; // 0x4c
	unsigned char CountryID; // 0x50
	char padding_1[3];
	int WeaponID; // 0x54
	UNITYENGINE_VECTOR3 oldpos; // 0x58
	char padding_2[4];
	uintptr botEquipment; // 0x68
	int Stats_Kills; // 0x70
	int Stats_Deads; // 0x74
	int pwID; // 0x78
	int swID; // 0x7c
	int mwID; // 0x80
	UNITYENGINE_VECTOR3 targetPosition; // 0x84
	bool inVehicle; // 0x90
	char padding_3[3];
	int inVehiclePos; // 0x94
	IL2CPP_STRING ClanName; // 0x98
	int ClanID; // 0xa0
	int AnimState; // 0xa4
	unsigned char Team; // 0xa8
	char padding_4[7];
	IL2CPP_STRING Name; // 0xb0
	bool Active; // 0xb8
	char padding_5[3];
	int State; // 0xbc
	float flash_time; // 0xc0
	char padding_6[4];
	uintptr mySound; // 0xc8
	uintptr goHelmets; // 0xd0
	uintptr goSkinMask; // 0xd8
	uintptr goMasks; // 0xe0
	uintptr goHats; // 0xe8
	uintptr goAttaches; // 0xf0
	bool zombie; // 0xf8
	char padding_7[3];
	int blockFlag; // 0xfc
	int currBlockType; // 0x100
	char padding_8[4];
	uintptr b; // 0x108
	uintptr bUp; // 0x110
	uintptr botPoser; // 0x118
	uintptr TC; // 0x120
};