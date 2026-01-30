#pragma once
#include "pch.h"

// classes (TypeInfo)
constexpr inline uintptr server_players_controller_class_offset = 0x35824E8;
constexpr inline uintptr client_class_offset = 0x35CE3F0;
constexpr inline uintptr sendpacket_class_offset = 0x35714F0;
constexpr inline uintptr ziploader_class_offset = 0x35E2D28;
constexpr inline uintptr playerprofile_class_offset = 0x35F4FB8;
constexpr inline uintptr gm_class_offset = 0x3569FE0;
constexpr inline uintptr connectioninfo_class_offset = 0x35D5A10;
constexpr inline uintptr const_class_offset = 0x35C3CB0;
constexpr inline uintptr scenemanager_class_offset = 0x3574E00;
constexpr inline uintptr map_class_offset = 0x35BE670;

// ws section 
constexpr inline uintptr weapon_raycast_offset = 0x630810;
constexpr inline uintptr send_packet_damage_offset = 0x48;
constexpr inline uintptr fpweaponreloader_canstart_reload_offset = 0x5FA330; 
constexpr inline uintptr map_getblock_offset = 0x656B80;

constexpr inline uintptr ziploader_instance_offset = 0x0;
constexpr inline uintptr ziploader_gamemode_offset = 0x24;

constexpr inline uintptr sendpacket_cmd_position_offset = 0x8;
constexpr inline uintptr sendpacket_cmd_damage_offset = 0x48;

constexpr inline uintptr client_sendposition_method_offset = 0x590200;
constexpr inline uintptr client_sendattack_method_offset = 0x58DC00;
constexpr inline uintptr client_update_method_offset = 0x56F600;
constexpr inline uintptr gm_currmainstate_offset = 0x0;

constexpr inline uintptr client_recvdamage_method_offset = 0x5724C0;
constexpr inline uintptr client_recvdamagehelmet_method_offset = 0x571DC0;
constexpr inline uintptr client_recvspawn_method_offset = 0x58A310;
constexpr inline uintptr vp_fpinput_inputattack_method_offset = 0x5ECB50;


