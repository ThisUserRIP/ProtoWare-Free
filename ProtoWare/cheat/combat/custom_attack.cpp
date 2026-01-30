#include "pch.h"
#include "custom_attack.h"
#include "config.h"

#include "game.h"
#include "gameoffsets.h"
#include "imgui.h"
#include "minhook.h"
#include "keycode.h"
#include "tracers.h"
#include "target_system.h"
#include "aim.h"
#include "attack_util.h"

#include "component.h"
#include "internal_camera.h"
#include "internal_component.h"
#include "internal_gameobject.h"
#include "internal_transform.h"

#include "stWeaponSystem.hpp"
#include "stPlayerHitboxData.hpp"
#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"
#include "stClient.hpp"
#include "stVP_FPController.hpp"
#include "stVP_FPCamera.hpp"
#include "stBotPoseController.hpp"
#include "stVP_FPWeaponHandler.hpp"
#include "stVP_Shooter.hpp"
#include "stAmmo.hpp"

#include "mdClient.hpp"
#include "mdCamera.hpp"
#include "mdRandom.hpp"
#include "mdPhysics.hpp"
#include "mdRaycastHit.hpp"
#include "mdParticleManager.hpp"
#include "mdWeaponSystem.hpp"
#include "mdObscuredInt.hpp"
#include "mdInput.hpp"
#include "mdTime.hpp"

typedef bool(__fastcall* DELEGATE_InputAttack)(uintptr _this);

DELEGATE_InputAttack inputattack_o;

void hkInputAttack(uintptr _this);

void custom_attack::initialize() {
	MH_CreateHook((void*)(gameassembly + vp_fpinput_inputattack_method_offset), &hkInputAttack, (void**)&inputattack_o);
	MH_EnableHook((void*)(gameassembly + vp_fpinput_inputattack_method_offset));
}

void hkInputAttack(uintptr _this) {
#define return_attack { inputattack_o(_this); return; }
    if (!config::custom_attack) return_attack;
    if (game::get_gs() != GS_GAME) return_attack;

	Client* client = game::get_client();
	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!client || !pcontroller || !pcontroller->RemotePlayersList || !pcontroller->PlayersLoaded) return;

    ServerBotData* ownbot = (ServerBotData*)pcontroller->RemotePlayersList->element(client->myindex);
    if (ownbot && ownbot->Dead) return;

	WeaponSystem* ws = (WeaponSystem*)pcontroller->csws;
	if(!ws) return;

    bool is_zombie = ws->CURRENT_WEAPON_ID == 35 || ws->CURRENT_WEAPON_ID == 37;
    bool is_melee = ws->CURRENT_WEAPON_ID != 0 && ws->CURRENT_WEAPON_ID == ws->mwid;
    bool is_primary = !is_zombie && ws->CURRENT_WEAPON_ID != 0 && ws->CURRENT_WEAPON_ID == ws->pwid;
    bool is_secondary = ws->CURRENT_WEAPON_ID != 0 && ws->CURRENT_WEAPON_ID == ws->swid;

	if (!is_primary && !is_melee && !is_secondary && !is_zombie) return_attack;
    if (is_secondary && ws->ammo_clip2 <= 0) return;
    if (is_primary && ws->ammo_clip <= 0) return;
    if (!Input__GetMouseButton(0)) return;
    
    if (is_primary) {
        if (!attack_util::try_shoot_pwid(ws, client)) return;
    }
    if (is_secondary) {
        if (!attack_util::try_shoot_swid(ws, client)) return;
    }
    if (is_melee || is_zombie) {
        if (!attack_util::try_shoot_melee(ws, client)) return;
    }
    
    if (is_primary) {
        ws->ammo_clip--;
        if (ws->csam) {
            Ammo* csam = (Ammo*)ws->csam;
            csam->clip = ws->ammo_clip;
        }
    }
    if (is_secondary) {
        ws->ammo_clip2--;
        if (ws->csam) {
            Ammo* csam = (Ammo*)ws->csam;
            csam->clip = ws->ammo_clip2;
        }
    }

    WeaponSystem__weapon_raycast((uintptr)ws, is_zombie ? ws->pwid : (is_melee ? ws->mwid : (is_secondary ? ws->swid : ws->pwid)), 256.0f, 256.0f, (uintptr)ws);

    if (is_primary && config::double_secondary_hit && ws->ammo_clip2 > 0 && attack_util::try_shoot_swid(ws, client)) {

        ws->ammo_clip2--;
        WeaponSystem__weapon_raycast((uintptr)ws, ws->swid, 40.0f, 40.0f, (uintptr)ws);
    }
}