#include "pch.h"
#include "movement.h"
#include "minhook.h"
#include "config.h"
#include "imgui.h"

#include "game.h"
#include "gameoffsets.h"
#include "globals.h"
#include "fast_raycast.h"
#include "target_system.h"

#include "component.h"
#include "internal_component.h"
#include "internal_camera.h"
#include "internal_transform.h"
#include "internal_gameobject.h"
#include "keycode.h"

#include "mdInput.hpp"
#include "mdClient.hpp"
#include "mdTime.hpp"
#include "mdObscuredInt.hpp"
#include "mdCamera.hpp"

#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"
#include "stVP_FPController.hpp"
#include "stVP_FPCamera.hpp"
#include "stVP_FPWeaponReloader.hpp"
#include "stWeaponSystem.hpp"
#include "stAmmo.hpp"
#include "stClient.hpp"
#include "stPlayerControl.hpp"
#include "stPlayerProfile.hpp"
#include <stVP_FPWeaponHandler.hpp>
#include <mdParticleManager.hpp>
#include <tracers.h>
#include <attack_util.h>

typedef bool(__fastcall* DELEGATE_CanStart_Reload)(vp_FPWeaponReloader* _this);
typedef bool(__fastcall* DELEGATE_ClientUpdate)(Client* _this);

void** null_pointer;
void null_func() {}
void* ret_null_func() { return nullptr; }

DELEGATE_CanStart_Reload canstart_reload_o;
DELEGATE_ClientUpdate clientupdate_o;
void* sendposition_o_null;

float send_pos_penalty = 0.0f;

internal_transform* movement_transform;
Client* movement_client;
vp_FPController* movement_fpcontroller;
vp_FPCamera* movement_fpcamera;

char player__monostring_buf[128];

char* player__transform_monostring(monostring* str) {
	WideCharToMultiByte(CP_UTF8, 0, str->wstring, -1, player__monostring_buf, 128, 0, 0);
	return player__monostring_buf;
}

IL2CPP_STRING shitIl2cppString(const char* text) {
	int len = strlen(text);
	int headerSize = sizeof(void*) * 2 + sizeof(int);
	int totalSize = headerSize + (len + 1) * 2;

	unsigned char* buf = (unsigned char*)malloc(totalSize);
	memset(buf, 0, totalSize);

	*(int*)(buf + sizeof(void*) * 2) = len;

	wchar_t* chars = (wchar_t*)(buf + headerSize);
	for (int i = 0; i < len; i++) {
		chars[i] = (wchar_t)text[i];
	}
	chars[len] = 0;

	return (IL2CPP_STRING)buf;
}

bool hkCanStart_Reload(vp_FPWeaponReloader* _this);
void hkSendPosition(Client* _this, uint8_t state);
void hkClientUpdate(Client* _this);
void process_under_placing();
void process_forward_attack();
void process_spider();
void process_tap_teleport();
void hMinigun_Update(void* _this);
void hInput_Update(void* _this);
void hvp_FPWeaponShooter_TryFire(void* _this);
void hFPWeaponHandler_Update(vp_FPWeaponHandler* _this);
//void hSpawnManager_Spawn(void*, float, float, float);
vec3 hvp_FPController_get_Velocity(vp_FPController* _this);
void UpdateMelee(void* _this);
void UpdateServers(void* _this);

typedef void(*Minigun_Func)(void*);
Minigun_Func oMinigun_Update;

typedef void(*vp_FPWeaponShooter_Func)(void*);
vp_FPWeaponShooter_Func ovp_FPWeaponShooter_TryFire;

typedef vec3(*vp_FPController_get_Vector3)(vp_FPController*);
vp_FPController_get_Vector3 ovp_FPController_get_Velocity;

typedef void(*Input_Updates)(void*);
Input_Updates oInput_Update;

typedef void(*Melee_Updates)(void*);
Melee_Updates oUpdateMelee;

typedef void(*Servers_Updates)(void*);
Servers_Updates oUpdateServers;

typedef void(*FPWeaponHandler_Updates)(vp_FPWeaponHandler*);
FPWeaponHandler_Updates oFPWeaponHandler_Update;

//typedef void(*SpawnManager_Updates)(void*, float,float,float);
//SpawnManager_Updates oSpawnManager_Spawn;

bool vp_FPWeaponShooter_TryFire = false;

//void hksend_attack(Client* _this, int weaponid, int victimid, int hitbox, bool alter_damage, vec3 a, vec3 v, vec3 c1, vec3 c2);

void movement::initialize() {
	MH_CreateHook((void*)(gameassembly + fpweaponreloader_canstart_reload_offset), &hkCanStart_Reload, (void**)&canstart_reload_o);
	MH_EnableHook((void*)(gameassembly + fpweaponreloader_canstart_reload_offset));

	MH_CreateHook((void*)(gameassembly + client_update_method_offset), &hkClientUpdate, (void**)&clientupdate_o);
	MH_EnableHook((void*)(gameassembly + client_update_method_offset));

	MH_CreateHook((void*)(gameassembly + client_sendposition_method_offset), &hkSendPosition, (void**)&sendposition_o_null);
	MH_EnableHook((void*)(gameassembly + client_sendposition_method_offset));

	MH_CreateHook((void*)(gameassembly + 0x53C0D0), &hMinigun_Update, (void**)&oMinigun_Update);
	MH_EnableHook((void*)(gameassembly + 0x53C0D0));

	MH_CreateHook((void*)(gameassembly + 0x5FE3B0), &hvp_FPWeaponShooter_TryFire, (void**)&ovp_FPWeaponShooter_TryFire);
	MH_EnableHook((void*)(gameassembly + 0x5FE3B0));

	MH_CreateHook((void*)(gameassembly + 0x5EC7B0), &hvp_FPController_get_Velocity, (void**)&ovp_FPController_get_Velocity);
	MH_EnableHook((void*)(gameassembly + 0x5EC7B0));

	MH_CreateHook((void*)(gameassembly + 0x5EEF60), &hInput_Update, (void**)&oInput_Update);
	MH_EnableHook((void*)(gameassembly + 0x5EEF60));

	MH_CreateHook((void*)(gameassembly + 0x5F9ED0), &hFPWeaponHandler_Update, (void**)&oFPWeaponHandler_Update);
	MH_EnableHook((void*)(gameassembly + 0x5F9ED0));

	MH_CreateHook((void*)(gameassembly + 0x6363E0), &UpdateMelee, (void**)&oUpdateMelee);
	MH_EnableHook((void*)(gameassembly + 0x6363E0));

	MH_CreateHook((void*)(gameassembly + 0x85E9F0), &UpdateServers, (void**)&oUpdateServers);
	MH_EnableHook((void*)(gameassembly + 0x85E9F0));

	/*MH_CreateHook((void*)(gameassembly + 0xA364F0), &hSpawnManager_Spawn, (void**)&oSpawnManager_Spawn);
	MH_EnableHook((void*)(gameassembly + 0xA364F0));*/

	//MH_CreateHook((void*)(gameassembly + client_sendattack_method_offset), &hksend_attack, (void**)&sendposition_o_null);
	//MH_EnableHook((void*)(gameassembly + client_sendattack_method_offset));
	fast_raycast::update();
}

void UpdateServers(void* _this) {
	oUpdateServers(_this);

	if (!_this) return;

	uintptr_t gameModeArray = *(uintptr_t*)((uintptr_t)_this + 0x58);
	if (gameModeArray) {
		int modeCount = *(int*)(gameModeArray + 0x18);
		for (int i = 0; i < modeCount; i++) {
			*(bool*)(gameModeArray + 0x20 + i) = true;
		}
	}
}

void hFPWeaponHandler_Update(vp_FPWeaponHandler* _this) {
	if (config::instantChangeWeapon) {
		_this->SetWeaponAttackSleepDuration = 0.f;
		_this->SetWeaponRefreshStatesDelay = 0.f;
		_this->SetWeaponDuration = 0.f;
		_this->SetWeaponReloadSleepDuration = 0.f;
		_this->SetWeaponZoomSleepDuration = 0.f;
	}

	oFPWeaponHandler_Update(_this);
}

void hInput_Update(void* _this) {

	oInput_Update(_this);

	if (config::noWeaponStopMove) {
		*(float*)((uintptr)_this + 0x60) = 0.0f;
	}
}

void hMinigun_Update(void* _this) {

	if (config::spinupMinigun)
	{
		*(float*)((uintptr)_this + 0x20) = 1000.f;
	}

	oMinigun_Update(_this);
}

void hvp_FPWeaponShooter_TryFire(void* _this)
{
	vp_FPWeaponShooter_TryFire = true;

	ovp_FPWeaponShooter_TryFire(_this);

	vp_FPWeaponShooter_TryFire = false;
}

vec3 hvp_FPController_get_Velocity(vp_FPController* _this)
{
	if (vp_FPWeaponShooter_TryFire && config::noWeaponStopMove)
	{
		return { 0, 0, 0 };
	}

	return ovp_FPController_get_Velocity(_this);
}

void UpdateMelee(void* _this) {
	if(config::destroy_speed)
		*(float*)((uintptr_t)_this + 0xB0) = config::SpeedBuild;

	oUpdateMelee(_this);
}

void update_move(Client* _this) {
	if (!_this->active) return;
	if (!_this->cspc) return;
	if (((PlayerControl*)_this->cspc)->freeze) return;

	float delta = 0.033f;

	if (config::fakeLag) {
		float time = Time__get_time();

		switch (config::fakeLagMode) {
		case 0:
			delta = config::sendPositionSpeed;
			break;

		case 1:
			delta = config::sendPositionSpeed * ((float)(rand() % 100) / 100.0f);
			break;

		case 2:
		{
			static bool sw = false;
			delta = sw ? 0.005f : config::sendPositionSpeed;
			if (send_pos_penalty > delta) sw = !sw;
		}
		break;

		case 3:
			delta = (sinf(time * 3.0f) * 0.5f + 0.5f) * config::sendPositionSpeed;
			break;

		case 4:
		{
			static int tick = 0;
			tick++;
			if (tick % 30 < 15) delta = config::sendPositionSpeed;
			else delta = 0.01f;
		}
		break;

		case 5:
			delta = config::sendPositionSpeed + (((rand() % 20) - 10) / 1000.0f);
			if (delta < 0) delta = 0;
			break;

		case 6:
			delta = (rand() % 2 == 0) ? 0.001f : config::sendPositionSpeed;
			break;

		case 7:
		{
			static int tick_s = 0;
			tick_s++;
			if ((tick_s / 10) % 2 == 0)
				delta = config::sendPositionSpeed;
			else
				delta = config::sendPositionSpeed * 0.2f;
		}
		break;

		case 8:
		{ 
			float factor = 0.5f + ((float)(rand() % 70) / 100.0f);
			delta = config::sendPositionSpeed * factor;
		}   
		break;

		case 9:
		{
			bool isMoving = (GetAsyncKeyState('W') || GetAsyncKeyState('A') ||
				GetAsyncKeyState('S') || GetAsyncKeyState('D'));

			if (isMoving)
				delta = config::sendPositionSpeed;
			else
				delta = 0.005f;
		}
		break;

		case 10:
		{
			float cycle = fmodf(time * 2.0f, 1.0f);
			delta = config::sendPositionSpeed * cycle;
		}
		break;

		case 11:
		{
			static int tick_p = 0;
			tick_p++;
			if ((tick_p % 18) < 15)
				delta = config::sendPositionSpeed;
			else
				delta = 0.001f;
		}
		break;
		}
	}

	send_pos_penalty += Time__get_deltaTime();
	if (send_pos_penalty > delta) {
		send_pos_penalty = 0.0f;
		Client__send_position((uintptr)_this, 11);
	}
}

void process_fast_reload() {
	if (!config::auto_fast_reload) return;

	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller) return;
	WeaponSystem* ws = (WeaponSystem*)pcontroller->csws;
	if (!ws) return;

	if (ws->CURRENT_WEAPON_ID == ws->pwid && ws->ammo_clip <= 0) {
		ws->ammo_clip = ws->ammo_fullclip;
		if (ws->csam) {
			Ammo* csam = (Ammo*)ws->csam;
			csam->clip = ws->ammo_fullclip;
		}
		Client__send_prereload(ws->cscl, ws->pwid, Time__get_time());
		Client__send_reload(ws->cscl, ws->pwid, Time__get_time());

		return;
	}
	if (ws->CURRENT_WEAPON_ID == ws->swid && ws->ammo_clip2 <= 0) {
		ws->ammo_clip2 = ws->ammo_fullclip2;
		if (ws->csam) {
			Ammo* csam = (Ammo*)ws->csam;
			csam->clip = ws->ammo_fullclip2;
		}
		Client__send_prereload(ws->cscl, ws->swid, Time__get_time());
		Client__send_reload(ws->cscl, ws->swid, Time__get_time());

		return;
	}
}

void process_custom_flag() {
	auto* profile = game::get_profile();
	if (!profile) return;
	profile->premium = 1;
	profile->country = 16;
	profile->NY2017Q = true;
	profile->NY2018Q = true;
	profile->VD2017Q = true;
	profile->jetpackFuel = 1000;
}

void movement::update() {
	if (game::get_gs() == GS_GAME) {
		process_fast_reload();
		process_custom_flag();

		ServerPlayersController* pcontroller = game::get_pcontroller();
		movement_client = game::get_client();
		if (!movement_client || !pcontroller || !pcontroller->FPController) return;

		//update_move();

		movement_fpcontroller = (vp_FPController*)pcontroller->FPController;

		if (config::speedModifier)
			*(float*)((uintptr)movement_fpcontroller + 0x1c0) = config::speedm; // MotorAcceleration

		if (config::jumpModifier)
			*(float*)((uintptr)movement_fpcontroller + 0x1D8) = config::jumpm;

		if (config::gravModifier)
			*(float*)((uintptr)movement_fpcontroller + 0x208) = config::gravm;

		if (config::strafec) {
			*(float*)((uintptr)movement_fpcontroller + 0x1C8) = 10.f;
			*(float*)((uintptr)movement_fpcontroller + 0x194) = 10.f;
		}

		if (!movement_fpcontroller->m_FPSCamera) return;
		movement_fpcamera = (vp_FPCamera*)movement_fpcontroller->m_FPSCamera;
		if (!movement_fpcamera->MyCamera) return;
		component* camera = (component*)movement_fpcamera->MyCamera;
		if (!camera->internal_component || !camera->internal_component->gameobject) return;
		movement_transform = camera->internal_component->gameobject->get_transform();
		if (!movement_transform) return;

		process_under_placing();
		process_forward_attack();

		process_spider();
		//process_tap_teleport();
	}
}

void process_spider() {
	if (!config::spider) return;
	if (!movement_fpcontroller || !movement_transform || !movement_fpcamera) return;

	float yawRad = movement_fpcamera->m_Yaw * 0.0174533f;
	vec3 ownpos = movement_transform->get_kernel_pos();

	float angles[3] = { 0.0f, -0.55f, 0.55f };
	float dist = 1.0f;
	bool wallFound = false;

	for (int i = 0; i < 3; i++) {
		float a = yawRad + angles[i];
		vec3 dir = vec3(sinf(a) * dist, 0, cosf(a) * dist);

		vec3 startLow = vec3(ownpos.x, ownpos.y + 0.6f, ownpos.z);
		vec3 endLow = startLow + dir;

		vec3 startHigh = vec3(ownpos.x, ownpos.y + 1.6f, ownpos.z);
		vec3 endHigh = startHigh + dir;

		if (fast_raycast::linecast_chk(startLow, endLow) || fast_raycast::linecast_chk(startHigh, endHigh)) {
			wallFound = true;
			break;
		}
	}

	if (wallFound && Input__GetKey(KeyCode_W) && Input__GetKey(KeyCode_Space)) {
		*(float*)((uintptr)movement_fpcontroller + 0x208) = -0.35f;
	}
	else if (*(float*)((uintptr)movement_fpcontroller + 0x208) == -0.35f) {
		*(float*)((uintptr)movement_fpcontroller + 0x208) = 0.2f;
	}
}

void process_tap_teleport() {
	if (!Input__GetKey(KeyCode_X)) return;
	if (!movement_fpcontroller || !movement_transform || !movement_fpcamera) return;

	static float last_tp = 0.0f;
	float current_time = Time__get_time();
	if (current_time - last_tp < 0.3f) return;

	vec3 origin = movement_transform->get_kernel_pos();
	vec3 target = vec3(0, 0, 0);
	bool found = false;

	for (int i = 2; i <= 6; i++) {
		vec3 blockPos = vec3(origin.x, origin.y + (float)i, origin.z);
		vec3 airPos = vec3(origin.x, origin.y + (float)i + 1.2f, origin.z);

		if (fast_raycast::contains_block(blockPos) && !fast_raycast::contains_block(airPos)) {
			target = origin;
			target.y += (float)i + 1.5f;
			found = true;
			break;
		}
	}

	if (!found) {
		float yaw = movement_fpcamera->m_Yaw * 0.0174533f;
		vec3 fwd = vec3(sinf(yaw), 0, cosf(yaw));

		vec3 wallCheck = vec3(origin.x + fwd.x, origin.y + 1.0f, origin.z + fwd.z);

		if (fast_raycast::contains_block(wallCheck)) {
			for (int h = 2; h <= 6; h++) {
				vec3 ledgeBase = vec3(origin.x + fwd.x, origin.y + (float)h, origin.z + fwd.z);
				vec3 ledgeTop = vec3(origin.x + fwd.x, origin.y + (float)h + 1.2f, origin.z + fwd.z);

				if (fast_raycast::contains_block(ledgeBase) && !fast_raycast::contains_block(ledgeTop)) {
					target = origin;
					target.x += fwd.x * 1.0f;
					target.z += fwd.z * 1.0f;
					target.y += (float)h + 1.5f;
					found = true;
					break;
				}
			}
		}
	}

	if (found) {
		*(float*)((uintptr)movement_fpcontroller + 0x208) = -5.0f;
		//*(float*)((uintptr)movement_fpcontroller + 0x1F4) = 0.15f;

		movement_fpcontroller->m_FixedPosition = target;
		movement_transform->set_kernel_pos(target);
		*(vec3*)((uintptr)movement_fpcontroller + 0xC4) = target;

		*(float*)((uintptr)movement_fpcontroller + 0x208) = 0.2f;

		last_tp = current_time;
	}
}

void process_under_placing() {
	if (!Input__GetKey(KeyCode_F2)) return;

	static float last_place_time = 0.0f;
	float current_time = Time__get_time();

	if (current_time - last_place_time < config::SpeedBuild) return;
	last_place_time = current_time;

	vec3 ownpos = movement_transform->get_kernel_pos();

	int bx = (int)floor(ownpos.x);
	int by = (int)floor(ownpos.y + 0.5f);
	int bz = (int)floor(ownpos.z);

	int placed_count = 0;
	int max_packets = (int)config::MaxPackets;
	int r = (int)config::radiusBuild;

	int y_start = -r;
	int y_end = r;

	if (config::buildMode == 0) { 
		y_start = -1; y_end = -1;
	}
	else if (config::buildMode == 3) {
		y_start = 0; y_end = 3;
	}
	else if (config::buildMode == 5) {
		y_start = 3; y_end = 3;
	}
	else if (config::buildMode == 6) {
		y_start = 0; y_end = r;
	}
	else if (config::buildMode == 7) {
		y_start = 0; y_end = r * 2;
	}
	else if (config::buildMode == 13) {
		y_start = -1; y_end = -1;
	}
	else if (config::buildMode == 14) {
		y_start = -1; y_end = r;
	}
	else if (config::buildMode == 15) {
		y_start = 0; y_end = 3;
	}

	float yaw = movement_fpcamera->m_Yaw * 0.0174533f;
	float sy = sinf(yaw);
	float cy = cosf(yaw);
	int fwdX = (int)round(sy);
	int fwdZ = (int)round(cy);

	for (int x = -r; x <= r; x++) {
		for (int y = y_start; y <= y_end; y++) {
			for (int z = -r; z <= r; z++) {
				if (placed_count >= max_packets) return;

				bool place = false;
				int dist_sq = x * x + y * y + z * z;
				int dist_flat = x * x + z * z;
				int r_sq = r * r;
				int r_inner = (r - 1) * (r - 1);

				switch (config::buildMode) {
				case 0:
					place = true;
					break;
				case 1:
					place = (abs(x) == r || abs(y) == r || abs(z) == r);
					break;
				case 2:
					place = (dist_sq <= r_sq && dist_sq >= r_inner);
					break;
				case 3:
					place = (abs(x) == r || abs(z) == r);
					break;
				case 4:
					place = (dist_flat <= r_sq && dist_flat >= r_inner);
					break;
				case 5:
					place = true;
					break;
				case 6:
					place = (abs(x) <= (r - y) && abs(z) <= (r - y));
					break;
				case 7: {
					float angle = atan2((float)z, (float)x) + 3.14159f;
					int expected_y = (int)((angle / 6.283f) * 4.0f);
					place = ((y % 4) == expected_y) && (abs(x) == r || abs(z) == r);
				} break;
				case 8: 
					place = (abs(x) == r && abs(z) == r);
					break;
				case 9:
					place = ((x + y + z) % 2 == 0) && (abs(x) == r || abs(y) == r || abs(z) == r);
					break;
				case 10:
					place = (x == 0 || z == 0);
					break;
				case 11:
					place = (abs(x) == abs(z));
					break;
				case 12:
					place = (dist_sq <= r_sq);
					break;
				case 13:
				{
					bool center = (x == 0 && abs(z) <= r) || (z == 0 && abs(x) <= r);
					bool arm1 = (x == -r && z > 0 && z <= (r / 2) + 1);
					bool arm2 = (z == r && x > 0 && x <= (r / 2) + 1);
					bool arm3 = (x == r && z < 0 && z >= -(r / 2) - 1);
					bool arm4 = (z == -r && x < 0 && x >= -(r / 2) - 1);
					place = center || arm1 || arm2 || arm3 || arm4;
				} break;
				case 14:
					place = (x == 0 && z == 0);
					break; 
				case 15: 
				{
					int wallDist = 2;
					if (abs(fwdX) > abs(fwdZ)) {
						place = (x == fwdX * wallDist && abs(z) <= r);
					}
					else {
						place = (z == fwdZ * wallDist && abs(x) <= r);
					}
				} break;
				}

				if (place) {
					int tx = bx + x;
					int ty = by + y;
					int tz = bz + z;

					if (!fast_raycast::contains_block(vec3(tx + 0.5f, ty + 0.5f, tz + 0.5f))) {
						Client__send_setblock((uintptr)movement_client, tx, ty, tz, current_time);
						placed_count++;
					}
				}
			}
		}
	}
}

void process_forward_attack() {
	if (!Input__GetKey(KeyCode_F3)) return;

	static float last_atk_time = 0.0f;
	float current_time = Time__get_time();

	if (current_time - last_atk_time < config::SpeedBuild) return;
	last_atk_time = current_time;

	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller) return;
	WeaponSystem* ws = (WeaponSystem*)pcontroller->csws;
	if (!ws) return;

	vec3 localPos = movement_transform->get_kernel_pos();

	int r = (int)config::radiusBuild;
	int packets_sent = 0;
	int max_packets = (int)config::MaxPackets;

	int y_min = -1;
	int y_max = 5;

	float yaw = movement_fpcamera->m_Yaw * 0.0174533f;
	float sy = sinf(yaw);
	float cy = cosf(yaw);

	for (int y = y_min; y <= y_max; y++) {
		for (int x = -r; x <= r; x++) {
			for (int z = -r; z <= r; z++) {
				if (packets_sent >= max_packets) return;

				bool should_break = false;
				vec3 offset = vec3((float)x, (float)y, (float)z);

				switch (config::nukerMode) {
				case 0:
					should_break = true;
					break;
				case 1:
					should_break = (y >= 0);
					break;
				case 2:
				{
					vec3 fwd = vec3(sy, 0, cy);
					vec3 dirToBlock = offset.get_normalized();
					float dot = fwd.dot(dirToBlock);
					should_break = (dot > 0.5f && abs(x) <= 2 && abs(z) <= 2 && y >= 0 && y <= 3);
				}
				break;
				}

				if (should_break) {
					vec3 targetPos = vec3(floor(localPos.x) + x + 0.5f, floor(localPos.y) + y + 0.5f, floor(localPos.z) + z + 0.5f);

					if (fast_raycast::contains_block(targetPos)) {
						vec3i blockpos = vec3i((int)targetPos.x, (int)targetPos.y, (int)targetPos.z);

						Client__send_attackblock((uintptr)movement_client,
							(uintptr)&blockpos,
							ws->mwid,
							false,
							&localPos,
							&targetPos);

						packets_sent++;
					}
				}
			}
		}
	}
}

bool hkCanStart_Reload(vp_FPWeaponReloader* _this) {
	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller || !pcontroller->csws) return canstart_reload_o(_this);

	WeaponSystem* ws = (WeaponSystem*)pcontroller->csws;
	if (ws->CURRENT_WEAPON_ID == ws->pwid) {
		ws->ammo_clip = ws->ammo_fullclip;
		if (ws->csam) {
			Ammo* csam = (Ammo*)ws->csam;
			csam->clip = ws->ammo_fullclip;
		}
		Client__send_prereload(ws->cscl, ws->pwid, Time__get_time());
		Client__send_reload(ws->cscl, ws->pwid, Time__get_time());

		return false;
	}
	if (ws->CURRENT_WEAPON_ID == ws->swid) {
		ws->ammo_clip2 = ws->ammo_fullclip2;
		if (ws->csam) {
			Ammo* csam = (Ammo*)ws->csam;
			csam->clip = ws->ammo_fullclip2;
		}
		Client__send_prereload(ws->cscl, ws->swid, Time__get_time());
		Client__send_reload(ws->cscl, ws->swid, Time__get_time());

		return false;
	}

	return canstart_reload_o(_this);
}

//void hkSendPosition(Client* _this, uint8_t state) {
//	// disabling jump start and end packets
//	// fixes ansynchronus calls, that reduce kicks
//	if (state == 3 || state == 4) return;
//
//	// to add own move send behaviour
//	if (state < 10) return;
//	state = 0;
//	static bool savePos = false;
//	static vec3 savedPos = { 0.f, 0.f, 0.f };
//	static bool selfKill = false;
//
//	uintptr obsucredIntCMD = *(uintptr*)(game::get_packetcmds_fields() + sendpacket_cmd_position_offset);
//	int cmd = ObscuredInt__get_value(obsucredIntCMD);
//
//	Client__BEGIN_WRITE((uintptr)_this, cmd, 1); // set ignore time to write own
//	float time = Time__get_time();
//	if (config::fakeLag) time += config::timeSendPadding;
//	Client__WRITE_LONG((uintptr)_this, (int)(float)(time * 1000.0)); // own time
//	{
//		component* managedUnityCamera = (component*)Camera__get_main();
//		internal_transform* camTransform = managedUnityCamera->internal_component->gameobject->get_transform();
//		quat camRot = camTransform->get_rot();
//		vec3 camEuler = camRot.to_euler_angles();
//
//		ServerPlayersController* pcontroller = game::get_pcontroller();
//		movement_fpcontroller = (vp_FPController*)pcontroller->FPController;
//
//		if (config::cam_rot_spoofing && target_system::target_valid) {
//			auto aim_targeted_bot = target_system::get_cached_target();
//			vec3 direction = (aim_targeted_bot.hit_pos - aim_targeted_bot.cam_pos).get_normalized();
//			camEuler = direction.to_euler();
//		}
//
//		if (config::fakeBackward && config::spin)
//		{
//			camEuler.x += rand() % 90;
//			camEuler.y += rand() % 180;
//		}
//		else if (config::fakeBackward)
//		{
//			camEuler.y += config::EulerBackward;
//		}
//
//		float pitchX = camEuler.x;
//		if (pitchX <= 0.0f || pitchX > 90.0f)
//		{
//			if (pitchX >= 270.0f && pitchX <= 360.0f)
//				pitchX = 360.0f - pitchX;
//		}
//		else
//		{
//			pitchX = pitchX * -1.0f;
//		}
//		/*if (pitchX > 0.f && pitchX <= 90.f)
//		{
//			pitchX *= -1.f;
//		}
//		else if (pitchX >= 270.f && pitchX <= 360.f)
//		{
//			pitchX = 360.f - pitchX;
//		} */
//		float finalPitch = pitchX + 90.0f;
//
//		if (config::stopSendPosition)
//		{
//			state = 0;
//			*(float*)((uintptr)movement_fpcontroller + 0x208) = 0;
//			return;
//		}
//		else if (config::stopSendPosition == false){
//			*(float*)((uintptr)movement_fpcontroller + 0x208) = 0.2f;
//		}
//
//		if (config::allwaysShift)
//		{
//			state = 1;
//		}
//
//		if (config::fakeDuck)
//		{
//			state = 2;
//		}
//
//		internal_gameobject* playerGO = (internal_gameobject*)(((component*)_this->LocalPlayer)->internal_component);
//		internal_transform* playerTrs = playerGO->get_transform();
//		vec3 playerPos = playerTrs->get_pos();
//
//		if (config::fakeDown)
//		{
//			pitchX = -90.f;
//			pcontroller->myLookPoint.x = playerPos.x;
//			pcontroller->myLookPoint.y = 0;
//			pcontroller->myLookPoint.z = playerPos.z;
//		}
//
//		if (config::ghost)
//		{
//			if (!savePos)
//			{
//				savedPos = playerPos;
//				savePos = true;
//			}
//
//			playerPos = savedPos;
//		}
//		else
//		{
//			savePos = false;
//			if (GetAsyncKeyState('B') & 1)
//			{
//				playerPos.y = NAN;
//				selfKill = true;
//			}
//		}
//
//		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)playerPos.x * 1000.0));
//		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)playerPos.y * 1000.0));
//		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)playerPos.z * 1000.0));
//
//		Client__WRITE_FLOAT((uintptr)_this, finalPitch);
//		if(config::own_look_y_spoofing)
//			Client__WRITE_FLOAT((uintptr)_this, camEuler.y);
//		else Client__WRITE_FLOAT((uintptr)_this, playerTrs->get_rot().to_euler_angles().y);
//
//		Client__WRITE_BYTE((uintptr)_this, state);
//		
//		if (config::lookpoint_spoofing && target_system::target_valid) {
//			auto aim_targeted_bot = target_system::get_cached_target();
//			Client__WRITE_LONG((uintptr)_this, (int)(float)((double)aim_targeted_bot.hit_pos.x * 1000.0));
//			Client__WRITE_LONG((uintptr)_this, (int)(float)((double)aim_targeted_bot.hit_pos.y * 1000.0));
//			Client__WRITE_LONG((uintptr)_this, (int)(float)((double)aim_targeted_bot.hit_pos.z * 1000.0));
//		}
//		else {
//			Client__WRITE_LONG((uintptr)_this, (int)(float)((double)pcontroller->myLookPoint.x * 1000.0));
//			Client__WRITE_LONG((uintptr)_this, (int)(float)((double)pcontroller->myLookPoint.y * 1000.0));
//			Client__WRITE_LONG((uintptr)_this, (int)(float)((double)pcontroller->myLookPoint.z * 1000.0));
//		}
//
//		movement::own_server_position = playerPos;
//	}
//
//	Client__WRITE_BYTE((uintptr)_this, 0);
//	int oldPos = _this->writepos;
//	_this->writepos = 2;
//	Client__WRITE_SHORT((uintptr)_this, oldPos);
//	_this->writepos = oldPos;
//	Client__SendPacket((uintptr)_this, 0);
//}

void hkSendPosition(Client* _this, uint8_t state) {
	if (state == 3 || state == 4) return;
	if (state < 10) return;
	state = 0;

	static bool savePos = false;
	static vec3 savedPos = { 0.f, 0.f, 0.f };
	static bool selfKill = false;

	internal_gameobject* playerGO = (internal_gameobject*)(((component*)_this->LocalPlayer)->internal_component);
	internal_transform* playerTrs = playerGO->get_transform();
	vec3 playerPos = playerTrs->get_pos();

	component* managedUnityCamera = (component*)Camera__get_main();
	internal_transform* camTransform = managedUnityCamera->internal_component->gameobject->get_transform();
	quat camRot = camTransform->get_rot();
	vec3 camEuler = camRot.to_euler_angles();

	ServerPlayersController* pcontroller = game::get_pcontroller();
	movement_fpcontroller = (vp_FPController*)pcontroller->FPController;

	if (config::cam_rot_spoofing && target_system::target_valid) {
		auto aim_targeted_bot = target_system::get_cached_target();
		vec3 direction = (aim_targeted_bot.hit_pos - aim_targeted_bot.cam_pos).get_normalized();
		camEuler = direction.to_euler();
	}

	if (config::fakeBackward)
	{
		static float s_angle = 0.0f;
		static int s_tick = 0;
		s_tick++;

		switch (config::aa_type)
		{
		case 0: 
			camEuler.y += config::EulerBackward;
			break;
		case 1: 
			s_angle += 55.0f;
			if (s_angle >= 360.0f) s_angle -= 360.0f;
			camEuler.y += s_angle;
			break;
		case 2: 
			s_angle += 15.0f;
			if (s_angle >= 360.0f) s_angle -= 360.0f;
			camEuler.y += s_angle;
			break;
		case 3: 
			camEuler.y += 180.0f;
			if (s_tick % 4 < 2) camEuler.y += 35.0f;
			else camEuler.y -= 35.0f;
			break;
		case 4: 
			camEuler.y += 180.0f;
			if (s_tick % 6 == 0) camEuler.y += 90.0f;
			else if (s_tick % 6 == 3) camEuler.y -= 90.0f;
			break;
		case 5: 
			if (s_tick % 60 < 30) 
			{ 
				s_angle += 45.0f; 
			camEuler.y += s_angle;
			}
			else { 
				camEuler.y += 180.0f + (sinf(Time__get_time() * 5.0f) * 45.0f); 
			} 
			break;
		}
	}

	float pitchX = camEuler.x;

	if (config::fakeBackward && config::aa_pitch_type != 0)
	{
		static int p_tick = 0;
		p_tick++;
		switch (config::aa_pitch_type) {
		case 1: 
			pitchX = -89.0f;
			break;
		case 2: 
			pitchX = 89.0f;
			break;
		case 3: 
			pitchX = 0.0f;
			break;
		case 4: 
			if (p_tick % 8 < 4) 
				pitchX = -89.0f;
			else pitchX = 89.0f;
			break;
		}
	}
	else
	{
		if (pitchX <= 0.0f || pitchX > 90.0f) {
			if (pitchX >= 270.0f && pitchX <= 360.0f) 
				pitchX = 360.0f - pitchX;
		}
		else { 
			pitchX = pitchX * -1.0f;
		}

		if (config::fakeDown && !config::fakeBackward) {
			pitchX = -90.f;
			pcontroller->myLookPoint.x = playerPos.x;
			pcontroller->myLookPoint.y = 0;
			pcontroller->myLookPoint.z = playerPos.z;
		}
	}

	camEuler.x = pitchX + 90.0f;

	if (config::stopSendPosition) {
		state = 0;
		*(float*)((uintptr)movement_fpcontroller + 0x208) = 0;
		return;
	}
	else if (config::stopSendPosition == false) {
		*(float*)((uintptr)movement_fpcontroller + 0x208) = 0.2f;
	}

	if (config::allwaysShift) state = 1;
	if (config::fakeDuck) state = 2;

	if (config::ghost) {
		if (!savePos) { 
			savedPos = playerPos;
			savePos = true;
		}
		playerPos = savedPos;
	}

	uintptr obsucredIntCMD = *(uintptr*)(game::get_packetcmds_fields() + sendpacket_cmd_position_offset);
	int cmd = ObscuredInt__get_value(obsucredIntCMD);

	Client__BEGIN_WRITE((uintptr)_this, cmd, 1);
	float time = Time__get_time();
	if (config::fakeLag) time += config::timeSendPadding;
	Client__WRITE_LONG((uintptr)_this, (int)(float)(time * 1000.0));

	Client__WRITE_LONG((uintptr)_this, (int)(float)((double)playerPos.x * 1000.0));
	Client__WRITE_LONG((uintptr)_this, (int)(float)((double)playerPos.y * 1000.0));
	Client__WRITE_LONG((uintptr)_this, (int)(float)((double)playerPos.z * 1000.0));

	Client__WRITE_FLOAT((uintptr)_this, camEuler.x);
	if (config::own_look_y_spoofing)
		Client__WRITE_FLOAT((uintptr)_this, camEuler.y);
	else
		Client__WRITE_FLOAT((uintptr)_this, playerTrs->get_rot().to_euler_angles().y);

	Client__WRITE_BYTE((uintptr)_this, state);

	if (config::lookpoint_spoofing && target_system::target_valid) {
		auto t = target_system::get_cached_target();
		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)t.hit_pos.x * 1000.0));
		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)t.hit_pos.y * 1000.0));
		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)t.hit_pos.z * 1000.0));
	}
	else {
		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)pcontroller->myLookPoint.x * 1000.0));
		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)pcontroller->myLookPoint.y * 1000.0));
		Client__WRITE_LONG((uintptr)_this, (int)(float)((double)pcontroller->myLookPoint.z * 1000.0));
	}

	movement::own_server_position = playerPos;

	Client__WRITE_BYTE((uintptr)_this, 0);
	int oldPos = _this->writepos;
	_this->writepos = 2;
	Client__WRITE_SHORT((uintptr)_this, oldPos);
	_this->writepos = oldPos;
	Client__SendPacket((uintptr)_this, 0);
}

void TeleportKill(Client* _this) {

}

void mov(Client* _this) {
	if (!config::magnet_player && !config::melee_strafe) return;

	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller || !pcontroller->RemotePlayersList) return;

	internal_gameobject* localGO = (internal_gameobject*)(((component*)_this->LocalPlayer)->internal_component);
	if (!localGO) return;
	internal_transform* localTrs = localGO->get_transform();
	vec3 localPos = localTrs->get_pos();

	ServerBotData* targetBot = nullptr;
	float closestDist = 9999.0f;

	deffor(i, pcontroller->RemotePlayersList->max_size) {
		if (i == _this->myindex) continue;
		ServerBotData* bot = (ServerBotData*)pcontroller->RemotePlayersList->element(i);

		if (isptrinvalid((uintptr)bot) || !bot->Active || bot->Dead) continue;

		if (bot->Name && config::targets.count > 0) {
			char* c_name = player__transform_monostring(bot->Name);
			for (int t = 0; t < config::targets.count; t++) {
				if (strcmp(c_name, config::targets[t].nickname_u8) == 0) {
					float d = localPos.get_distance(bot->position);
					if (d < closestDist) {
						closestDist = d;
						targetBot = bot;
					}
					break;
				}
			}
		}
	}

	if (!targetBot) return;
	if (closestDist > 5.0f) return;

	vec3 targetPos = targetBot->position;
	float time = Time__get_time();

	static float next_ground_touch = 0.0f;
	bool touching_ground = false;

	if (time > next_ground_touch) {
		if (time > next_ground_touch + 0.15f) {
			next_ground_touch = time + 3.5f;
		}
		else {
			touching_ground = true;
		}
	}

	vec3 newPos = targetPos;

	if (config::melee_strafe) {
		float speed = config::strafeSpeed;
		float angle = time * speed;

		newPos.x = targetPos.x + cosf(angle) * config::dist_strafe;
		newPos.z = targetPos.z + sinf(angle) * config::dist_strafe;

		if (touching_ground) newPos.y = targetPos.y;
		else newPos.y = targetPos.y + 0.5f;
	}
	else if (config::magnet_player) {
		newPos.x = targetPos.x;
		newPos.z = targetPos.z;

		if (touching_ground) newPos.y = targetPos.y;
		else newPos.y = targetPos.y + 1.2f;
	}

	localTrs->set_kernel_pos(newPos);
}

void hkClientUpdate(Client* _this) {
	update_move(_this);
	//TeleportKill(_this);
	mov(_this);

	if (game::get_gs() == GS_GAME) {

		if (config::auto_respawn) {
			static float death_start_time = 0.0f;

			ServerPlayersController* pcontroller = game::get_pcontroller();

			if (pcontroller && pcontroller->RemotePlayersList) {
				ServerBotData* ownbot = (ServerBotData*)pcontroller->RemotePlayersList->element(_this->myindex);

				if (ownbot) {
					if (ownbot->Dead) {
						float time = Time__get_time();

						if (death_start_time == 0.0f) {
							death_start_time = time;
						}

						if (time >= death_start_time + 0.5f) {
							Client__send_spawn_me((uintptr)_this);
							death_start_time = 0.0f;
						}
					}
					else {
						death_start_time = 0.0f;
					}
				}
			}
		}

		if (config::auto_team_switch) {
			static bool switched_this_death = false;

			ServerPlayersController* pcontroller = game::get_pcontroller();

			if (pcontroller && pcontroller->RemotePlayersList) {
				ServerBotData* ownbot = (ServerBotData*)pcontroller->RemotePlayersList->element(_this->myindex);

				if (ownbot) {
					if (ownbot->Dead) {
						if (!switched_this_death) {
							Client__send_jointeam((uintptr)_this, (unsigned char)config::auto_team_select, 0);
							Client__send_spawn_me((uintptr)_this);

							switched_this_death = true;
						}
					}
					else {
						switched_this_death = false;
					}
				}
			}
		}

		if (config::chat_spam) {
			static float next_spam_time = 0.0f;
			float time = ImGui::GetTime();

			if (time >= next_spam_time) {
				next_spam_time = time + 3.0f;

				IL2CPP_STRING message = shitIl2cppString("report about a cheater tg: @NHO_MAIN");
				Client__send_chat((uintptr)_this, 0, message);
			}
		}
	}

	clientupdate_o(_this);
}