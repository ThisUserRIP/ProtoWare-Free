#include "pch.h"
#include "globals.h"
#include "monostring.h"
#include "tarray.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define IL2CPP_STRING monostring*
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline void Client__Awake(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x569530))(__this);
}

inline uintptr Client__LateConnect(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56e050))(__this);
}

inline void Client__StartLateAuth(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56f500))(__this);
}

inline uintptr Client__LateAuth(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56dfe0))(__this);
}

inline void Client__SendPacket(uintptr __this, bool isReliable) {
	((void(__fastcall*)(uintptr, bool))(GAME_ASSEMBLY_PTR + 0x56f320))(__this, isReliable);
}

inline void Client__Update(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56f600))(__this);
}

inline void Client__SendMyPosition(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56f1a0))(__this);
}

inline void Client__OnApplicationQuit(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x42ae10))(__this);
}

inline void Client__OnConnected(uintptr __this, uintptr Id) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x56e330))(__this, Id);
}

inline void Client__OnDisconnected(uintptr __this, uintptr Id) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x56e3e0))(__this, Id);
}

inline void Client__OnBinaryMessageReceived(uintptr __this, IL2CPP_ARRAY buffer, __int64 offset, __int64 size) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, __int64, __int64))(GAME_ASSEMBLY_PTR + 0x56e0c0))(__this, buffer, offset, size);
}

inline void Client__OnTcpError(uintptr __this, IL2CPP_STRING msg) {
	((void(__fastcall*)(uintptr, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x56ec10))(__this, msg);
}

inline void Client__Disconnect(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56a0e0))(__this);
}

inline void Client__ProcessData(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x56ec60))(__this, buffer, len);
}

inline void Client__InitRecvDelegates(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56ab20))(__this);
}

inline void Client__recv_eos(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x574f90))(__this, buffer, len);
}

inline void Client__recv_report_status(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589ad0))(__this, buffer, len);
}

inline void Client__recv_auth(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5706b0))(__this, buffer, len);
}

inline void Client__recv_position(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x588cd0))(__this, buffer, len);
}

inline void Client__recv_playerinfo(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x587c00))(__this, buffer, len);
}

inline void Client__recv_myinfo(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x587600))(__this, buffer, len);
}

inline void Client__recv_ping(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x587ae0))(__this, buffer, len);
}

inline void Client__recv_blockattack(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x570b40))(__this, buffer, len);
}

inline void Client__recv_blockinfo(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x570be0))(__this, buffer, len);
}

inline void Client__recv_block_destroy(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5709f0))(__this, buffer, len);
}

inline void Client__recv_scores(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589cf0))(__this, buffer, len);
}

inline void Client__recv_jointeamclass(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576630))(__this, buffer, len);
}

inline void Client__recv_spawn(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58a310))(__this, buffer, len);
}

inline void Client__recv_ready_for_spawn(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5894b0))(__this, buffer, len);
}

inline void Client__recv_spawnequip(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58a4e0))(__this, buffer, len);
}

inline void Client__recv_set_weapon(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589f20))(__this, buffer, len);
}

inline void Client__recv_zm_countdown(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58cb10))(__this, buffer, len);
}

inline void Client__recv_zm_message(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58d110))(__this, buffer, len);
}

inline void Client__recv_zm_infect(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58cbf0))(__this, buffer, len);
}

inline void Client__recv_attack_milk(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5705e0))(__this, buffer, len);
}

inline void Client__recv_setblock(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58a120))(__this, buffer, len);
}

inline void Client__recv_damage(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5724c0))(__this, buffer, len);
}

inline void Client__recv_chat(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5710e0))(__this, buffer, len);
}

inline void Client__recv_stats(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58b820))(__this, buffer, len);
}

inline void Client__recv_currentweapon(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571ca0))(__this, buffer, len);
}

inline void Client__recv_disconnect(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x573aa0))(__this, buffer, len);
}

inline void Client__recv_reconnect(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589930))(__this, buffer, len);
}

inline void Client__recv_endofsnap(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x42ae10))(__this, buffer, len);
}

inline void Client__recv_buildblock(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x570e60))(__this, buffer, len);
}

inline void Client__recv_my_data(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x577c30))(__this, buffer, len);
}

inline void Client__recv_damage_helmet(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571dc0))(__this, buffer, len);
}

inline void Client__recv_createent(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571620))(__this, buffer, len);
}

inline void Client__recv_destroy_status(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5737b0))(__this, buffer, len);
}

inline void Client__recv_explode(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x575a10))(__this, buffer, len);
}

inline void Client__recv_private_info(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589430))(__this, buffer, len);
}

inline void Client__recv_reconnect2(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5897d0))(__this, buffer, len);
}

inline void Client__recv_sethealth(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58a1b0))(__this, buffer, len);
}

inline void Client__recv_gamemessage(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576190))(__this, buffer, len);
}

inline uintptr Client__camPause(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x5702f0))(__this);
}

inline void Client__recv_equip(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x575090))(__this, buffer, len);
}

inline void Client__recv_app_disconnect(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x570570))(__this, buffer, len);
}

inline void Client__recv_message(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576d60))(__this, buffer, len);
}

inline void Client__recv_ct_MiniMapRadar(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571b60))(__this, buffer, len);
}

inline void Client__recv_game_version(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576010))(__this, buffer, len);
}

inline void Client__recv_dealed_damage(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x573290))(__this, buffer, len);
}

inline void Client__recv_damage_armor(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571d60))(__this, buffer, len);
}

inline void Client__recv_sound_fx(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58a250))(__this, buffer, len);
}

inline void Client__recv_reposition(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589b80))(__this, buffer, len);
}

inline void Client__recv_moveent(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x577760))(__this, buffer, len);
}

inline void Client__recv_destroyent(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x573860))(__this, buffer, len);
}

inline void Client__recv_entposition(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x574a10))(__this, buffer, len);
}

inline void Client__recv_moveboss(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x577470))(__this, buffer, len);
}

inline void Client__recv_movecube(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x577590))(__this, buffer, len);
}

inline void Client__recv_change_skin(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x570f80))(__this, buffer, len);
}

inline void Client__recv_weapons_set(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58c370))(__this, buffer, len);
}

inline void Client__recv_liftup(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576870))(__this, buffer, len);
}

inline void Client__recv_enter_the_ent(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x573f20))(__this, buffer, len);
}

inline void Client__SetBotCollider(uintptr __this, int id, bool value) {
	((void(__fastcall*)(uintptr, int, bool))(GAME_ASSEMBLY_PTR + 0x56f390))(__this, id, value);
}

inline uintptr Client__SetTankSkin(uintptr __this, uintptr tex, uintptr mat) {
	return ((uintptr(__fastcall*)(uintptr, uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x56f470))(__this, tex, mat);
}

inline void Client__recv_exit_the_ent(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x575140))(__this, buffer, len);
}

inline void Client__recv_vehicle_turret(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58c150))(__this, buffer, len);
}

inline void Client__recv_vehicle_health(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58bc10))(__this, buffer, len);
}

inline void Client__recv_vehicle_explode(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58baa0))(__this, buffer, len);
}

inline void Client__recv_vehicle_hit(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58be20))(__this, buffer, len);
}

inline void Client__recv_vehicle_targeting(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x42ae10))(__this, buffer, len);
}

inline void Client__recv_ent_health(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x573b10))(__this, buffer, len);
}

inline void Client__recv_gungame_player(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576520))(__this, buffer, len);
}

inline void Client__recv_zplayerpos(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58d1b0))(__this, buffer, len);
}

inline void Client__recv_zentpos(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x58c560))(__this, buffer, len);
}

inline void Client__recv_chunk(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571370))(__this, buffer, len);
}

inline void Client__recv_chunk_finish(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x571300))(__this, buffer, len);
}

inline void Client__recv_mapdata(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x576b10))(__this, buffer, len);
}

inline void Client__recv_flag_set(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x575c10))(__this, buffer, len);
}

inline void Client__recv_flag_update(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x575ea0))(__this, buffer, len);
}

inline void Client__recv_accept_weapons(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x570360))(__this, buffer, len);
}

inline void Client__recv_selected_block(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x589eb0))(__this, buffer, len);
}

inline void Client__recv_api_force_update(uintptr __this, IL2CPP_ARRAY buffer, int len) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x5704e0))(__this, buffer, len);
}

inline void Client__send_auth(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x58e0c0))(__this);
}

inline void Client__send_position(uintptr __this, unsigned char state) {
	((void(__fastcall*)(uintptr, unsigned char))(GAME_ASSEMBLY_PTR + 0x590200))(__this, state);
}

inline void Client__send_myinfo(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x58fcd0))(__this);
}

inline void Client__send_eos(uintptr __this, IL2CPP_ARRAY data) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x58ef80))(__this, data);
}

inline void Client__send_blockinfo(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x58e420))(__this);
}

inline void Client__send_jointeam(uintptr __this, unsigned char _team, unsigned char _class) {
	((void(__fastcall*)(uintptr, unsigned char, unsigned char))(GAME_ASSEMBLY_PTR + 0x58f570))(__this, _team, _class);
}

inline void Client__send_attackblock(uintptr __this, uintptr c, int weaponid, bool alter_damage, UNITYENGINE_VECTOR3 c1, UNITYENGINE_VECTOR3 c2) {
	((void(__fastcall*)(uintptr, uintptr, int, bool, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x58dea0))(__this, c, weaponid, alter_damage, c1, c2);
}

inline void Client__send_jointeam_auto(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x58f220))(__this);
}

inline void Client__send_chat(uintptr __this, unsigned char teamsay, IL2CPP_STRING msg) {
	((void(__fastcall*)(uintptr, unsigned char, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x58e530))(__this, teamsay, msg);
}

inline void Client__send_report(uintptr __this, int plID, int reportType) {
	((void(__fastcall*)(uintptr, int, int))(GAME_ASSEMBLY_PTR + 0x591080))(__this, plID, reportType);
}

inline void Client__send_last_config(uintptr __this, unsigned char _team) {
	((void(__fastcall*)(uintptr, unsigned char))(GAME_ASSEMBLY_PTR + 0x58f6b0))(__this, _team);
}

inline void Client__send_attack_ent(uintptr __this, int uid, int wid, bool alter_damage, UNITYENGINE_VECTOR3 a, UNITYENGINE_VECTOR3 v, UNITYENGINE_VECTOR3 c1, UNITYENGINE_VECTOR3 c2) {
	((void(__fastcall*)(uintptr, int, int, bool, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x58d9c0))(__this, uid, wid, alter_damage, a, v, c1, c2);
}

inline void Client__send_new_config(uintptr __this, int _mwid, int _pwid, int _swid, int _ammo1, int _ammo2, int _ammo3, int _gr1, int _gr2) {
	((void(__fastcall*)(uintptr, int, int, int, int, int, int, int, int))(GAME_ASSEMBLY_PTR + 0x58fde0))(__this, _mwid, _pwid, _swid, _ammo1, _ammo2, _ammo3, _gr1, _gr2);
}

inline void Client__send_milk(uintptr __this, int weaponid, bool alter_damage) {
	((void(__fastcall*)(uintptr, int, bool))(GAME_ASSEMBLY_PTR + 0x58fa30))(__this, weaponid, alter_damage);
}

inline void Client__send_setblock(uintptr __this, int x, int y, int z, float fvalue) {
	((void(__fastcall*)(uintptr, int, int, int, float))(GAME_ASSEMBLY_PTR + 0x591440))(__this, x, y, z, fvalue);
}

inline void Client__send_currentweapon(uintptr __this, int weaponid) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x58e9c0))(__this, weaponid);
}

inline void Client__send_disconnect(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x58ed60))(__this);
}

inline void Client__send_selectblock(uintptr __this, unsigned char flag) {
	((void(__fastcall*)(uintptr, unsigned char))(GAME_ASSEMBLY_PTR + 0x591300))(__this, flag);
}

inline void Client__send_ping(uintptr __this, float TimeOfRequest) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x5900d0))(__this, TimeOfRequest);
}

inline void Client__send_savemap(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x5911f0))(__this);
}

inline void Client__send_private_settings(uintptr __this, int gamemode, int mapid) {
	((void(__fastcall*)(uintptr, int, int))(GAME_ASSEMBLY_PTR + 0x590e10))(__this, gamemode, mapid);
}

inline void Client__send_spawn_me(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x591600))(__this);
}

inline void Client__send_prereload(uintptr __this, int weaponid, float fvalue) {
	((void(__fastcall*)(uintptr, int, float))(GAME_ASSEMBLY_PTR + 0x5908a0))(__this, weaponid, fvalue);
}

inline void Client__send_reload(uintptr __this, int weaponid, float fvalue) {
	((void(__fastcall*)(uintptr, int, float))(GAME_ASSEMBLY_PTR + 0x590f60))(__this, weaponid, fvalue);
}

inline void Client__send_private_command(uintptr __this, int cmd, int pid, int param1) {
	((void(__fastcall*)(uintptr, int, int, int))(GAME_ASSEMBLY_PTR + 0x5909c0))(__this, cmd, pid, param1);
}

inline void Client__send_private_command(uintptr __this, int cmd, int pid, int param1, unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2, unsigned char z1, unsigned char z2) {
	((void(__fastcall*)(uintptr, int, int, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char))(GAME_ASSEMBLY_PTR + 0x590b50))(__this, cmd, pid, param1, x1, x2, y1, y2, z1, z2);
}

inline void Client__send_medkit(uintptr __this, int medkit) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x58f8f0))(__this, medkit);
}

inline void Client__send_enter_the_ent(uintptr __this, int ent_id, int pos_id) {
	((void(__fastcall*)(uintptr, int, int))(GAME_ASSEMBLY_PTR + 0x58ee50))(__this, ent_id, pos_id);
}

inline void Client__send_spawn_my_vehicle(uintptr __this, int wid) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x591740))(__this, wid);
}

inline void Client__send_createent(uintptr __this, UNITYENGINE_VECTOR3 pos, UNITYENGINE_VECTOR3 rot, UNITYENGINE_VECTOR3 force, UNITYENGINE_VECTOR3 torque, int enttypeid) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x58e7a0))(__this, pos, rot, force, torque, enttypeid);
}

inline void Client__send_exit_the_ent(uintptr __this, int ent_id) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x58f100))(__this, ent_id);
}

inline void Client__send_vehicle_turret(uintptr __this, UNITYENGINE_VECTOR3 T_r, float T_lr, UNITYENGINE_VECTOR3 G_lr, int ent_id) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, float, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x591c80))(__this, T_r, T_lr, G_lr, ent_id);
}

inline void Client__send_vehicle_targeting(uintptr __this, int id) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x591b40))(__this, id);
}

inline void Client__send_detonateent(uintptr __this, int uid, UNITYENGINE_VECTOR3 pos) {
	((void(__fastcall*)(uintptr, int, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x58ec10))(__this, uid, pos);
}

inline void Client__send_use_module(uintptr __this, int module_index) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x591a20))(__this, module_index);
}

inline void Client__send_detonate_my_c4(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x58ead0))(__this);
}

inline void Client__send_tnt(uintptr __this, int x, int y, int z, float fvalue) {
	((void(__fastcall*)(uintptr, int, int, int, float))(GAME_ASSEMBLY_PTR + 0x591860))(__this, x, y, z, fvalue);
}

inline void Client__send_new_ent_pos(uintptr __this, int uid, UNITYENGINE_VECTOR3 pos) {
	((void(__fastcall*)(uintptr, int, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x58ff80))(__this, uid, pos);
}

inline void Client__send_attack(uintptr __this, int weaponid, int victimid, int hitbox, bool alter_damage, UNITYENGINE_VECTOR3 a, UNITYENGINE_VECTOR3 v, UNITYENGINE_VECTOR3 c1, UNITYENGINE_VECTOR3 c2) {
	((void(__fastcall*)(uintptr, int, int, int, bool, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x58dc00))(__this, weaponid, victimid, hitbox, alter_damage, a, v, c1, c2);
}

inline void Client__send_mission_status(uintptr __this, int mID) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x58fbb0))(__this, mID);
}

inline void Client__BEGIN_WRITE(uintptr __this, unsigned char cmd, bool ignore_time) {
	((void(__fastcall*)(uintptr, unsigned char, bool))(GAME_ASSEMBLY_PTR + 0x569ad0))(__this, cmd, ignore_time);
}

inline void Client__WRITE_RAW(uintptr __this, IL2CPP_ARRAY barray) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x56fd10))(__this, barray);
}

inline void Client__WRITE_BYTE(uintptr __this, unsigned char bvalue) {
	((void(__fastcall*)(uintptr, unsigned char))(GAME_ASSEMBLY_PTR + 0x56fa50))(__this, bvalue);
}

inline void Client__WRITE_SHORT(uintptr __this, uintptr svalue) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x56fd90))(__this, svalue);
}

inline void Client__WRITE_FLOAT(uintptr __this, float fvalue) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x56fa90))(__this, fvalue);
}

inline void Client__WRITE_LONG(uintptr __this, int ivalue) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x56fbe0))(__this, ivalue);
}

inline void Client__WRITE_STRING_CLASSIC(uintptr __this, IL2CPP_STRING svalue) {
	((void(__fastcall*)(uintptr, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x56fe60))(__this, svalue);
}

inline void Client__WRITE_STRING(uintptr __this, IL2CPP_STRING svalue) {
	((void(__fastcall*)(uintptr, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x56ffc0))(__this, svalue);
}

inline int Client__WRITE_LEN(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56fbd0))(__this);
}

inline void Client__END_WRITE(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56a2b0))(__this);
}

inline IL2CPP_ARRAY Client__EncodeShort(uintptr __this, uintptr inShort) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x56a5f0))(__this, inShort);
}

inline IL2CPP_ARRAY Client__EncodeInteger(uintptr __this, int inInt) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x56a470))(__this, inInt);
}

inline IL2CPP_ARRAY Client__EncodeFloat(uintptr __this, float inFloat) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x56a420))(__this, inFloat);
}

inline IL2CPP_ARRAY Client__EncodeStringUTF8(uintptr __this, IL2CPP_STRING inString) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x56a730))(__this, inString);
}

inline IL2CPP_ARRAY Client__EncodeStringASCII(uintptr __this, IL2CPP_STRING inString) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x56a640))(__this, inString);
}

inline IL2CPP_ARRAY Client__EncodeVector2(uintptr __this, UNITYENGINE_VECTOR2 inObject) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x56a820))(__this, inObject);
}

inline IL2CPP_ARRAY Client__EncodeVector3(uintptr __this, UNITYENGINE_VECTOR3 inObject) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x56a8f0))(__this, inObject);
}

inline IL2CPP_ARRAY Client__EncodeVector4(uintptr __this, UNITYENGINE_VECTOR4 inObject) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, UNITYENGINE_VECTOR4))(GAME_ASSEMBLY_PTR + 0x56a9f0))(__this, inObject);
}

inline IL2CPP_ARRAY Client__EncodeQuaternion(uintptr __this, UNITYENGINE_QUATERNION inObject) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, UNITYENGINE_QUATERNION))(GAME_ASSEMBLY_PTR + 0x56a4c0))(__this, inObject);
}

inline IL2CPP_ARRAY Client__EncodeColor(uintptr __this, uintptr inObject) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x56a2f0))(__this, inObject);
}

inline int Client__DecodeShort(uintptr __this, IL2CPP_ARRAY inBytes, int pos) {
	return ((int(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x569e50))(__this, inBytes, pos);
}

inline uintptr Client__DecodeShort2(uintptr __this, IL2CPP_ARRAY inBytes, int pos) {
	return ((uintptr(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x569df0))(__this, inBytes, pos);
}

inline int Client__DecodeInteger(uintptr __this, IL2CPP_ARRAY inBytes, int pos) {
	return ((int(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x569ce0))(__this, inBytes, pos);
}

inline float Client__DecodeSingle(uintptr __this, IL2CPP_ARRAY inBytes, int pos) {
	return ((float(__fastcall*)(uintptr, IL2CPP_ARRAY, int))(GAME_ASSEMBLY_PTR + 0x569eb0))(__this, inBytes, pos);
}

inline UNITYENGINE_VECTOR2 Client__DecodeVector2(uintptr __this, IL2CPP_ARRAY inBytes) {
	return ((UNITYENGINE_VECTOR2(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x569f10))(__this, inBytes);
}

inline UNITYENGINE_VECTOR3 Client__DecodeVector3(uintptr __this, IL2CPP_ARRAY inBytes) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x569f90))(__this, inBytes);
}

inline UNITYENGINE_VECTOR4 Client__DecodeVector4(uintptr __this, IL2CPP_ARRAY inBytes) {
	return ((UNITYENGINE_VECTOR4(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x56a030))(__this, inBytes);
}

inline UNITYENGINE_QUATERNION Client__DecodeQuaternion(uintptr __this, IL2CPP_ARRAY inBytes) {
	return ((UNITYENGINE_QUATERNION(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x569d40))(__this, inBytes);
}

inline uintptr Client__DecodeColor(uintptr __this, IL2CPP_ARRAY inBytes) {
	return ((uintptr(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x569c30))(__this, inBytes);
}

inline void Client__OnGUI(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56e4c0))(__this);
}

inline void Client__BEGIN_READ(uintptr __this, IL2CPP_ARRAY inBytes, int len, int startpos) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY, int, int))(GAME_ASSEMBLY_PTR + 0x569a80))(__this, inBytes, len, startpos);
}

inline int Client__READ_BYTE(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56eef0))(__this);
}

inline int Client__READ_LONG(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56f000))(__this);
}

inline IL2CPP_STRING Client__READ_STRING(uintptr __this) {
	return ((IL2CPP_STRING(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56f0a0))(__this);
}

inline float Client__READ_COORD(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x56ef50))(__this);
}

inline void Client__ctor(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x570150))(__this);
}

inline void Client__cctor() {
	((void(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x570110))();
}
