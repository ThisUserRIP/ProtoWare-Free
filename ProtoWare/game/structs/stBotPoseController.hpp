#include "pch.h"
#include "il2cpp_structs.h"
#include "tarray.h"

#define IL2CPP_CLASS il2cpp_class*
#define IL2CPP_ARRAY tarray*

struct BotPoseController {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	uintptr myAIM; // 0x18
	uintptr myLook; // 0x20
	uintptr myTarget; // 0x28
	uintptr myRenderer; // 0x30
	uintptr protectObject; // 0x38
	uintptr protectRenderer; // 0x40
	uintptr BodyRoot; // 0x48
	uintptr healthImage; // 0x50
	IL2CPP_ARRAY upperBodyChain; // 0x58, Transform[]
	IL2CPP_ARRAY AnimalGO; // 0x60, GameObject[]
	IL2CPP_ARRAY AnimalAnim; // 0x68, Animator[]
	int currentAnimal; // 0x70
	char padding_0[4];
	uintptr anim; // 0x78
	float sliderval; // 0x80
	float sliderval_rotation_y; // 0x84
	bool crouch; // 0x88
	char padding_1[7];
	uintptr MyData; // 0x90
	bool isProtected; // 0x98
	char padding_2[3];
	float protectTimer; // 0x9c
	int myTeam; // 0xa0
	char padding_3[4];
	IL2CPP_ARRAY TeamColors; // 0xa8, Color[]
	float xval; // 0xb0
	float xval_lerp; // 0xb4
	float _maxHealth; // 0xb8
};