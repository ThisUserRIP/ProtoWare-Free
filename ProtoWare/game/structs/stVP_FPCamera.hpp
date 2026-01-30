#include "pch.h"
#include "il2cpp_structs.h"
#include "math3d.h"

#define IL2CPP_CLASS il2cpp_class*
#define UNITYENGINE_VECTOR2 vec2
#define UNITYENGINE_VECTOR3 vec3
#define UNITYENGINE_VECTOR4 quat
#define UNITYENGINE_QUATERNION quat

struct component;
struct vp_FPCamera {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	component* __interalObj;
	char padding_0[128];
	uintptr MyCamera; // 0x98
	uintptr MyCameraBrain; // 0xa0
	uintptr FPController; // 0xa8
	bool MouseFreeze; // 0xb0
	char padding_1[3];
	UNITYENGINE_VECTOR2 MouseSensitivityRestore; // 0xb4
	int MouseSmoothSteps; // 0xbc
	float MouseSmoothWeight; // 0xc0
	bool MouseAcceleration; // 0xc4
	char padding_2[3];
	float MouseAccelerationThreshold; // 0xc8
	UNITYENGINE_VECTOR2 m_MouseMove; // 0xcc
	char padding_3[4];
	uintptr m_MouseSmoothBuffer; // 0xd8
	float RenderingFieldOfView; // 0xe0
	float RenderingZoomDamping; // 0xe4
	float m_FinalZoomTime; // 0xe8
	UNITYENGINE_VECTOR3 PositionOffset; // 0xec
	float PositionGroundLimit; // 0xf8
	float PositionSpringStiffness; // 0xfc
	float PositionSpringDamping; // 0x100
	float PositionSpring2Stiffness; // 0x104
	float PositionSpring2Damping; // 0x108
	float PositionKneeling; // 0x10c
	int PositionKneelingSoftness; // 0x110
	float PositionEarthQuakeFactor; // 0x114
	uintptr m_PositionSpring; // 0x118
	uintptr m_PositionSpring2; // 0x120
	bool m_DrawCameraCollisionDebugLine; // 0x128
	char padding_4[3];
	UNITYENGINE_VECTOR2 RotationPitchLimit; // 0x12c
	UNITYENGINE_VECTOR2 RotationYawLimit; // 0x134
	float RotationSpringStiffness; // 0x13c
	float RotationSpringDamping; // 0x140
	float RotationKneeling; // 0x144
	int RotationKneelingSoftness; // 0x148
	float RotationStrafeRoll; // 0x14c
	float RotationEarthQuakeFactor; // 0x150
	float m_Pitch; // 0x154
	float m_Yaw; // 0x158
	char padding_5[4];
	uintptr m_RotationSpring; // 0x160
	UNITYENGINE_VECTOR2 m_InitialRotation; // 0x168
	float ShakeSpeed; // 0x170
	UNITYENGINE_VECTOR3 ShakeAmplitude; // 0x174
	UNITYENGINE_VECTOR3 m_Shake; // 0x180
	UNITYENGINE_VECTOR4 BobRate; // 0x18c
	UNITYENGINE_VECTOR4 BobAmplitude; // 0x19c
	float BobInputVelocityScale; // 0x1ac
	float BobMaxInputVelocity; // 0x1b0
	bool BobRequireGroundContact; // 0x1b4
	char padding_6[3];
	float m_LastBobSpeed; // 0x1b8
	UNITYENGINE_VECTOR4 m_CurrentBobAmp; // 0x1bc
	UNITYENGINE_VECTOR4 m_CurrentBobVal; // 0x1cc
	float m_BobSpeed; // 0x1dc
	uintptr BobStepCallback; // 0x1e0
	float BobStepThreshold; // 0x1e8
	float m_LastUpBob; // 0x1ec
	bool m_BobWasElevating; // 0x1f0
	char padding_7[3];
	UNITYENGINE_VECTOR3 m_CameraCollisionStartPos; // 0x1f4
	UNITYENGINE_VECTOR3 m_CameraCollisionEndPos; // 0x200
	uintptr m_CameraHit; // 0x20c
	char padding_8[36];
	uintptr m_Player; // 0x238
};