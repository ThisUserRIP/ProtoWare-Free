#include "pch.h"
#include "internal_component.h"
#include "il2cpp_structs.h"
#include "tarray.h"
#include "math3d.h"

#define IL2CPP_CLASS il2cpp_class*
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2
#define UNITYENGINE_VECTOR3 vec3
#define UNITYENGINE_VECTOR4 quat
#define UNITYENGINE_QUATERNION quat

struct internal_component;

struct vp_FPController {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	internal_component* __internalObj;
	char padding_0[128];
	uintptr m_FPSCamera; // 0x98
	uintptr m_Map; // 0xa0
	uintptr m_PrevPosition; // 0xa8
	uintptr m_CharacterController; // 0xb0
	UNITYENGINE_VECTOR3 m_FixedPosition; // 0xb8
	UNITYENGINE_VECTOR3 m_SmoothPosition; // 0xc4
	uintptr client; // 0xd0
	bool fake1; // 0xd8
	bool fake2; // 0xd9
	bool m_HeadContact; // 0xda
	bool fake3; // 0xdb
	bool fake4; // 0xdc
	bool m_Grounded; // 0xdd
	bool m_NETGrounded; // 0xde
	bool fake5; // 0xdf
	char padding_1[180];
	float m_FallImpact; // 0x190
	float m_MotorAirSpeedModifier; // 0x194
	float m_CurrentAntiBumpOffset; // 0x198
	float m_SlopeFactor; // 0x19c
	UNITYENGINE_VECTOR3 m_MoveDirection; // 0x1a0
	UNITYENGINE_VECTOR2 m_MoveVector; // 0x1ac
	UNITYENGINE_VECTOR3 m_MotorThrottle; // 0x1b4
	float MotorAcceleration; // 0x1c0
	float MotorDamping; // 0x1c4
	float MotorAirSpeed; // 0x1c8
	float MotorSlopeSpeedUp; // 0x1cc
	float MotorSlopeSpeedDown; // 0x1d0
	bool MotorFreeFly; // 0x1d4
	char padding_5[3];
	float MotorJumpForce; // 0x1d8
	float MotorJumpForceDamping; // 0x1dc
	float MotorJumpForceHold; // 0x1e0
	float MotorJumpForceHoldDamping; // 0x1e4
	int m_MotorJumpForceHoldSkipFrames; // 0x1e8
	float m_MotorJumpForceAcc; // 0x1ec
	bool m_MotorJumpDone; // 0x1f0
	char padding_6[3];
	float m_FallSpeed; // 0x1f4
	float m_LastFallSpeed; // 0x1f8
	float m_HighestFallSpeed; // 0x1fc
	float PhysicsForceDamping; // 0x200
	float PhysicsPushForce; // 0x204
	float PhysicsGravityModifier; // 0x208
	float PhysicsSlopeSlideLimit; // 0x20c
	float PhysicsSlopeSlidiness; // 0x210
	float PhysicsWallBounce; // 0x214
	float PhysicsWallFriction; // 0x218
	bool PhysicsHasCollisionTrigger; // 0x21c
	char padding_7[3];
	uintptr m_Trigger; // 0x220
	UNITYENGINE_VECTOR3 m_ExternalForce; // 0x228
	char padding_8[4];
	IL2CPP_ARRAY m_SmoothForceFrame; // 0x238, Vector3[]
	bool m_Slide; // 0x240
	bool m_SlideFast; // 0x241
	char padding_9[2];
	float m_SlideFallSpeed; // 0x244
	float m_OnSteepGroundSince; // 0x248
	float m_SlopeSlideSpeed; // 0x24c
	UNITYENGINE_VECTOR3 m_PredictedPos; // 0x250
	UNITYENGINE_VECTOR3 m_PrevPos; // 0x25c
	UNITYENGINE_VECTOR3 m_PrevDir; // 0x268
	UNITYENGINE_VECTOR3 m_NewDir; // 0x274
	float m_ForceImpact; // 0x280
	float m_ForceMultiplier; // 0x284
	UNITYENGINE_VECTOR3 CapsuleBottom; // 0x288
	UNITYENGINE_VECTOR3 CapsuleTop; // 0x294
	float m_SkinWidth; // 0x2a0
	char padding_10[4];
	uintptr m_Platform; // 0x2a8
	UNITYENGINE_VECTOR3 m_PositionOnPlatform; // 0x2b0
	float m_LastPlatformAngle; // 0x2bc
	UNITYENGINE_VECTOR3 m_LastPlatformPos; // 0x2c0
	float m_NormalHeight; // 0x2cc
	UNITYENGINE_VECTOR3 m_NormalCenter; // 0x2d0
	float m_CrouchHeight; // 0x2dc
	UNITYENGINE_VECTOR3 m_CrouchCenter; // 0x2e0
	float m_AnimalHeight; // 0x2ec
	float m_AnimalRadius; // 0x2f0
	UNITYENGINE_VECTOR3 m_AnimalCenter; // 0x2f4
	uintptr b; // 0x300
	uintptr bUp; // 0x308
	int currBlockType; // 0x310
	char padding_11[4] ;
	uintptr myTransform; // 0x318
	uintptr attachedSound; // 0x320
	bool check_m_Grounded; // 0x328
	char padding_12[7];
	IL2CPP_ARRAY vecData; // 0x330, Vector3[]
	int vecDataPos; // 0x338
	char padding_13[4];
	uintptr m_Player; // 0x340
	float originalStepOffset; // 0x348
	float maxspeed; // 0x34c
	UNITYENGINE_VECTOR3 m_PrevPos_; // 0x350
	int m_PosError; // 0x35c
	UNITYENGINE_VECTOR3 oldPos; // 0x360
	float lastcheck; // 0x36c
};