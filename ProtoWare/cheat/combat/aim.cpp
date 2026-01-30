#include "pch.h"
#include "aim.h"
#include "imgui.h"

#include "config.h"
#include "fast_raycast.h"
#include "target_system.h"
#include "direct_melee.h"
#include "attack_util.h"
#include "unmanaged_list.hpp"

#include "game.h"
#include "gameoffsets.h"
#include "globals.h"
#include "minhook.h"
#include "keycode.h"
#include "tracers.h"

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

void* null_aim_hook_data;

void hk_weapon_raycast(WeaponSystem* _this, int wid, float dist, unsigned int blockdist, uintptr unused_ws);

void aim::initialize() {
    MH_CreateHook((void*)(gameassembly + weapon_raycast_offset), &hk_weapon_raycast, &null_aim_hook_data);
    MH_EnableHook((void*)(gameassembly + weapon_raycast_offset));
}

void aim::update() {
    bool pressed_mwid = Input__GetKey(KeyCode_C);
    bool pressed_swid = Input__GetKey(KeyCode_V);
    if (!pressed_mwid && !pressed_swid) return;

    Client* client = game::get_client();
    ServerPlayersController* pcontroller = game::get_pcontroller();
    if (!client || !pcontroller) return;

    WeaponSystem* ws = (WeaponSystem*)pcontroller->csws;

    component* mainCam = (component*)Camera__get_main();
    if (!mainCam) return;

    internal_transform* owntrs = ((internal_component*)client->__internalObj)->gameobject->get_transform();

    if (pressed_mwid) {
        bool is_zombie = ws->CURRENT_WEAPON_ID == 35 || ws->CURRENT_WEAPON_ID == 37;
        bool is_melee = ws->CURRENT_WEAPON_ID != 0 && ws->CURRENT_WEAPON_ID == ws->mwid;

        auto aim_targeted_bot = direct_melee::get_nearby_player(4.0f);
        if (!aim_targeted_bot.success) goto SWID;

        if (!attack_util::try_shoot_melee(ws, client)) goto SWID;

        ParticleManager__CreateHit(ws->cspm, (uintptr)owntrs->default_component, 1, aim_targeted_bot.hitpos.x, aim_targeted_bot.hitpos.y, aim_targeted_bot.hitpos.z);
        ParticleManager__CreateParticle(ws->cspm, aim_targeted_bot.hitpos.x, aim_targeted_bot.hitpos.y, aim_targeted_bot.hitpos.z, 1.0, 0.0, 0.0, 1.0);

        tracers::punch(aim_targeted_bot.campos, aim_targeted_bot.hitpos);

        Client__send_attack((uintptr)ws->cscl, is_zombie ? ws->pwid : ws->mwid, aim_targeted_bot.player_index, 1, false,
            &aim_targeted_bot.ownpos, &aim_targeted_bot.enemypos, &aim_targeted_bot.campos, &aim_targeted_bot.hitpos);
    }
SWID:
    if (pressed_swid) {
        if (!target_system::target_valid) return;
        auto aim_targeted_bot = target_system::cached_target;

        if (ws->ammo_clip2 <= 0) return;
        if (!attack_util::try_shoot_swid(ws, client)) return;

        ws->ammo_clip2--;
        if (ws->CURRENT_WEAPON_ID == ws->swid && ws->csam) {
            Ammo* csam = (Ammo*)ws->csam;
            csam->clip = ws->ammo_clip2;
        }

        ParticleManager__CreateHit(ws->cspm, (uintptr)owntrs->default_component, 1, aim_targeted_bot.hit_pos.x, aim_targeted_bot.hit_pos.y, aim_targeted_bot.hit_pos.z);
        ParticleManager__CreateParticle(ws->cspm, aim_targeted_bot.hit_pos.x, aim_targeted_bot.hit_pos.y, aim_targeted_bot.hit_pos.z, 1.0, 0.0, 0.0, 1.0);

        tracers::punch(aim_targeted_bot.cam_pos, aim_targeted_bot.hit_pos);

        vec3 ownpos = owntrs->get_kernel_pos();
        Client__send_attack((uintptr)ws->cscl, ws->swid, aim_targeted_bot.bot_index, 1, false,
            &ownpos, &aim_targeted_bot.bot_pos, &aim_targeted_bot.cam_pos, &aim_targeted_bot.hit_pos);
    }
}

void hk_weapon_raycast(WeaponSystem* _this, int wid, float dist, unsigned int blockdist, uintptr unused_ws) {
    if (!_this->cscl) {
        _this->cscl = (uintptr)game::get_client();
        if (!_this->cscl) return;
    }

    if (config::hideWeapon)
        WeaponSystem__HideWeapons((uintptr)_this, true);

    component* mainCam = (component*)Camera__get_main();
    if (!mainCam) return;

    float realdist = dist;
    if (wid == _this->mwid || wid == 35 || wid == 37)
        realdist = 4.0f;

    auto aim_targeted_bot = target_system::get_cached_target();
    if (aim_targeted_bot.hit_pos.get_distance(aim_targeted_bot.cam_pos) > dist) return;

    if (aim_targeted_bot.compromated_hit) {
        internal_transform* owntrs = ((internal_component*)_this->__internalObj)->gameobject->get_transform();
        vec3 ownpos = owntrs->get_kernel_pos();
        vec3 campos = ((internal_camera*)mainCam->internal_component)->go->get_transform()->get_pos();
        vec3 enemypos = aim_targeted_bot.bot_pos;
        if (aim_targeted_bot.compromated_campos) campos = aim_targeted_bot.cam_pos;

        ParticleManager__CreateHit(_this->cspm, (uintptr)owntrs->default_component, 1, aim_targeted_bot.hit_pos.x, aim_targeted_bot.hit_pos.y, aim_targeted_bot.hit_pos.z);
        ParticleManager__CreateParticle(_this->cspm, aim_targeted_bot.hit_pos.x, aim_targeted_bot.hit_pos.y, aim_targeted_bot.hit_pos.z, 1.0, 0.0, 0.0, 1.0);

        tracers::punch(campos, aim_targeted_bot.hit_pos);

        Client__send_attack((uintptr)_this->cscl, wid, aim_targeted_bot.bot_index, 1, false,
            &ownpos, &enemypos, &campos, &aim_targeted_bot.hit_pos);
        return;
    }

    vec3 screenCenter = vec3(screen_width / 2.0f, screen_height / 2.0f, 0);
    ray3d ray;
    Camera__ScreenPointToRay((uintptr)&ray, (uintptr)mainCam, &screenCenter);
    if (aim_targeted_bot.bot_data)
        ray.direction = ((aim_targeted_bot.bot_pos + vec3(0, 1.63f, 0)) - ray.origin).get_normalized();

    int layermask = _this->layerMask;

    rayhit3d hit;
    if (!Physics__Raycast((uintptr)&ray, (uintptr)&hit, dist, layermask)) {
        Client__send_milk((uintptr)_this->cscl, wid, _this->specialAttack);
        return;
    }

    vec3 campos = ((internal_camera*)mainCam->internal_component)->go->get_transform()->get_pos();
    rayhit3d hit2;
    //if (Physics__Linecast(&campos, &hit.point, (uintptr)&hit2)) {
    //    Client__send_milk((uintptr)_this->cscl, wid, _this->specialAttack);
    //    return;
    //}

    internal_transform* hittrs = (internal_transform*)((component*)RaycastHit__get_transform((uintptr)&hit))->internal_component;
    if (hittrs->go->name[0] == '(') {

        char blockpos[16];
        WeaponSystem__GetCursorUnderRay((uintptr)&blockpos, (uintptr)_this, true, blockdist, (uintptr)&ray);
        if (!blockpos[0]) return;
        WeaponSystem__weapon_attack_block((uintptr)_this, wid, ((uintptr)&blockpos) + 4, hit.point.x, hit.point.y, hit.point.z, hit.point.x, hit.point.y, hit.point.z, _this->specialAttack);
        return;
    }

    PlayerHitBoxData* data = (PlayerHitBoxData*)hittrs->go->get_component("PlayerHitBoxData");
    if (!data) {
        Client__send_milk((uintptr)_this->cscl, wid, _this->specialAttack);
        return;
    }

    internal_transform* owntrs = ((internal_component*)_this->__internalObj)->gameobject->get_transform();

    vec3 ownpos = owntrs->get_kernel_pos();
    vec3 enemypos = hittrs->get_pos();

    ParticleManager__CreateHit(_this->cspm, (uintptr)owntrs->default_component, data->hitzone, hit.point.x, hit.point.y, hit.point.z);
    ParticleManager__CreateParticle(_this->cspm, hit.point.x, hit.point.y, hit.point.z, 1.0, 0.0, 0.0, 1.0);
    tracers::punch(campos, hit.point);

    Client__send_attack((uintptr)_this->cscl, wid, data->index, data->hitzone, false,
        &ownpos, &enemypos, &campos, &hit.point);
}