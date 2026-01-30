#include "pch.h"
#include "attack_util.h"

#include "game.h"
#include "gameoffsets.h"
#include "imgui.h"

#include "component.h"
#include "internal_component.h"
#include "internal_gameobject.h"

#include "stClient.hpp"
#include "stWeaponSystem.hpp"
#include "stVP_FPWeaponHandler.hpp"
#include "stVP_Shooter.hpp"

#include "mdTime.hpp"

float attack_util::get_melee_attack_time(WeaponSystem* ws, Client* client) {
    if (ws->pwid == 35 || ws->pwid == 37) return 0.5f;

    vp_FPWeaponHandler* fpweaponhandler = (vp_FPWeaponHandler*)((internal_component*)client->__internalObj)->gameobject->get_component("vp_FPWeaponHandler");
    if (!fpweaponhandler) return -666.0f;

    float attackSpeed = -666.0f;

    deffor(i, fpweaponhandler->m_Weapons->size) {
        component* fpweapon = (component*)fpweaponhandler->m_Weapons->array->element(i);
        if (!fpweapon || (uintptr)fpweapon < 0x10000000000) continue;
        int weaponID = *((int*)((uintptr)fpweapon + 0x364));
        if (weaponID != ws->mwid) continue;

        uintptr animator = (uintptr)fpweapon->internal_component->gameobject->get_component("vp_WeaponAnimator");
        if (!animator) continue;
        attackSpeed = *((float*)((uintptr)animator + 0xb0));
    }

    return attackSpeed;
}


float attack_util::get_pwid_attack_time(WeaponSystem* ws, Client* client) {
    vp_FPWeaponHandler* fpweaponhandler = (vp_FPWeaponHandler*)((internal_component*)client->__internalObj)->gameobject->get_component("vp_FPWeaponHandler");
    if (!fpweaponhandler) return -666.0f;

    float attackDistance = 200.0f;
    float attackSpeed = -666.0f;

    deffor(i, fpweaponhandler->m_Weapons->size) {
        component* fpweapon = (component*)fpweaponhandler->m_Weapons->array->element(i);
        if (!fpweapon || (uintptr)fpweapon < 0x10000000000) continue;
        int weaponID = *((int*)((uintptr)fpweapon + 0x364));
        if (weaponID != ws->pwid) continue;

        vp_Shooter* shooter = (vp_Shooter*)fpweapon->internal_component->gameobject->get_component("vp_FPWeaponShooter");
        if (!shooter) continue;
        attackSpeed = shooter->ProjectileFiringRate;
    }
    if (ws->pwid == 34) attackSpeed *= 2.0f;

    return attackSpeed;
}

float attack_util::get_swid_attack_time(WeaponSystem* ws, Client* client) {
    vp_FPWeaponHandler* fpweaponhandler = (vp_FPWeaponHandler*)((internal_component*)client->__internalObj)->gameobject->get_component("vp_FPWeaponHandler");
    if (!fpweaponhandler) return -666.0f;

    float attackDistance = 200.0f;
    float attackSpeed = -666.0f;

    deffor(i, fpweaponhandler->m_Weapons->size) {
        component* fpweapon = (component*)fpweaponhandler->m_Weapons->array->element(i);
        if (!fpweapon || (uintptr)fpweapon < 0x10000000000) continue;
        int weaponID = *((int*)((uintptr)fpweapon + 0x364));
        if (weaponID != ws->swid) continue;

        vp_Shooter* shooter = (vp_Shooter*)fpweapon->internal_component->gameobject->get_component("vp_FPWeaponShooter");
        if (!shooter) continue;
        attackSpeed = shooter->ProjectileFiringRate;
    }

    return attackSpeed;
}

bool attack_util::try_shoot_melee(WeaponSystem* ws, Client* client) {
    float currentTime = Time__get_realtimeSinceStartup();
    float attackSpeed = get_melee_attack_time(ws, client);
    if (attackSpeed == -666.0f) return false;
    if (melee_next_attack_time > currentTime) return false;
    melee_next_attack_time = currentTime + attackSpeed;
    melee_start_attack_time = currentTime;
    return true;
}

bool attack_util::try_shoot_pwid(WeaponSystem* ws, Client* client) {
    float currentTime = Time__get_realtimeSinceStartup();
    float attackSpeed = get_pwid_attack_time(ws, client);
    if (attackSpeed == -666.0f) return false;
        if (pwid_next_attack_time > currentTime) return false;
    pwid_next_attack_time = currentTime + attackSpeed;
    pwid_start_attack_time = currentTime;
    return true;
}

bool attack_util::try_shoot_swid(WeaponSystem* ws, Client* client) {
    float currentTime = Time__get_realtimeSinceStartup();
    float attackSpeed = get_swid_attack_time(ws, client);
    if (attackSpeed == -666.0f) return false;
    if (swid_next_attack_time > currentTime) return false;
    swid_next_attack_time = currentTime + attackSpeed;
    swid_start_attack_time = currentTime;
    return true;
}

void attack_util::draw_shoot_delays() {
    float currentTime = Time__get_realtimeSinceStartup();

    // melee
MELEE:
    {
        if (melee_next_attack_time < currentTime) goto PRIMARY;
        float overallTime = melee_next_attack_time - melee_start_attack_time;

        float percent = 1.0f - ((melee_next_attack_time - currentTime) / overallTime);

        float sliderWidth = 60.0f;
        float sliderHeight = 10.0f;
        float sliderContentPadding = 2.0f;
        float sliderYPadding = 15.0f;

        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        draw_list->AddRectFilled(
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f), (screen_height / 2.0f) + sliderYPadding),
            ImVec2((screen_width / 2.0f) + (sliderWidth / 2.0f), (screen_height / 2.0f) + sliderYPadding + sliderHeight),
            IM_COL32(35, 35, 35, 255));
        draw_list->AddRectFilled(
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f) + sliderContentPadding, (screen_height / 2.0f) + sliderYPadding + sliderContentPadding),
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f) + (sliderWidth * percent) - sliderContentPadding, (screen_height / 2.0f) + sliderYPadding + sliderHeight - sliderContentPadding),
            IM_COL32(0, 255, 0, 255));
    }
    // primary
PRIMARY:
    {
        if (pwid_next_attack_time < currentTime) goto SECONDARY;
        float overallTime = pwid_next_attack_time - pwid_start_attack_time;

        float percent = 1.0f - ((pwid_next_attack_time - currentTime) / overallTime);

        float sliderWidth = 60.0f;
        float sliderHeight = 10.0f;
        float sliderContentPadding = 2.0f;
        float sliderYPadding = 30.0f;

        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        draw_list->AddRectFilled(
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f), (screen_height / 2.0f) + sliderYPadding),
            ImVec2((screen_width / 2.0f) + (sliderWidth / 2.0f), (screen_height / 2.0f) + sliderYPadding + sliderHeight),
            IM_COL32(35, 35, 35, 255));
        draw_list->AddRectFilled(
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f) + sliderContentPadding, (screen_height / 2.0f) + sliderYPadding + sliderContentPadding),
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f) + (sliderWidth * percent) - sliderContentPadding, (screen_height / 2.0f) + sliderYPadding + sliderHeight - sliderContentPadding),
            IM_COL32(255, 100, 0, 255));
    }
    // secondary
SECONDARY:
    {
        if (swid_next_attack_time < currentTime) goto NEXT;
        float overallTime = swid_next_attack_time - swid_start_attack_time;

        float percent = 1.0f - ((swid_next_attack_time - currentTime) / overallTime);

        float sliderWidth = 60.0f;
        float sliderHeight = 10.0f;
        float sliderContentPadding = 2.0f;
        float sliderYPadding = 45.0f;

        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        draw_list->AddRectFilled(
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f), (screen_height / 2.0f) + sliderYPadding),
            ImVec2((screen_width / 2.0f) + (sliderWidth / 2.0f), (screen_height / 2.0f) + sliderYPadding + sliderHeight),
            IM_COL32(35, 35, 35, 255));
        draw_list->AddRectFilled(
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f) + sliderContentPadding, (screen_height / 2.0f) + sliderYPadding + sliderContentPadding),
            ImVec2((screen_width / 2.0f) - (sliderWidth / 2.0f) + (sliderWidth * percent) - sliderContentPadding, (screen_height / 2.0f) + sliderYPadding + sliderHeight - sliderContentPadding),
            IM_COL32(255, 255, 0, 255));
    }
NEXT:
    return;
}