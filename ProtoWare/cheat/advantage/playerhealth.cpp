#include "pch.h"
#include "playerhealth.h"

#include "game.h"
#include "gameoffsets.h"
#include "globals.h"
#include "minhook.h"
#include "tarray.h"
#include "unmanaged_list.hpp"

#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"

struct internal_health_pair {
	int idx;
	int health;
	bool tykva;
};
typedef bool(__fastcall* DELEGATE_RecvSpawn)(uintptr _this, tarray* buffer, int len);
typedef bool(__fastcall* DELEGATE_RecvDamageHelmet)(uintptr _this, tarray* buffer, int len);

DELEGATE_RecvSpawn recvspawn_o;
DELEGATE_RecvDamageHelmet recvdamagehelmet_o;
unmanaged_list<internal_health_pair> internal_health_list;

void hkRecvSpawn(uintptr _this, tarray* buffer, int len);
void hkRecvDamageHelmet(uintptr _this, tarray* buffer, int len);

void playerhealth::initialize() {
	MH_CreateHook((void*)(gameassembly + client_recvspawn_method_offset), &hkRecvSpawn, (void**)&recvspawn_o);
	MH_EnableHook((void*)(gameassembly + client_recvspawn_method_offset));
	MH_CreateHook((void*)(gameassembly + client_recvdamagehelmet_method_offset), &hkRecvDamageHelmet, (void**)&recvdamagehelmet_o);
	MH_EnableHook((void*)(gameassembly + client_recvdamagehelmet_method_offset));
}

void playerhealth::update() {
	if (game::get_gs() == GS_GAME) return;
	internal_health_list.clearfast();
}

void playerhealth::registrate_health(int index, int health, int tykva) {
	revfor(i, internal_health_list.count) {
		if (internal_health_list[i].idx == index) {

			if(health != -666)
				internal_health_list[i].health = health;

			if (tykva == 1) internal_health_list[i].tykva = false;
			else if (tykva == 2) internal_health_list[i].tykva = true;

			return;
		}
	}
	internal_health_list.push({ index,health, (tykva == 2 ? true : false) });
}
int playerhealth::get_player_health(int index) {
	revfor(i, internal_health_list.count) {
		if (internal_health_list[i].idx == index)
			return internal_health_list[i].health;
	}
	return -1;
}
bool playerhealth::get_player_tykva(int index) {
	revfor(i, internal_health_list.count) {
		if (internal_health_list[i].idx == index)
			return internal_health_list[i].tykva;
	}
	return false;
}

void hkRecvSpawn(uintptr _this, tarray* buffer, int len) {
	uintptr bufferptr = (uintptr)&buffer->array;

	int playerID = *((unsigned char*)(bufferptr + 4));
	int x = *((unsigned char*)(bufferptr + 5));
	int y = *((unsigned char*)(bufferptr + 6));
	int z = *((unsigned char*)(bufferptr + 7));

	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller || !pcontroller->RemotePlayersList) {
		playerhealth::registrate_health(playerID, 100, 1);
		recvspawn_o(_this, buffer, len);
		return;
	}
	ServerBotData* bot = (ServerBotData*)pcontroller->RemotePlayersList->element(playerID);
	if (!bot->Item) {
		playerhealth::registrate_health(playerID, 100, 1);
		recvspawn_o(_this, buffer, len);
		return;
	}
	int item = bot->Item->element(6, 4);
	//int item = bot->Item->element(6, 4);
	//int item2 = bot->Item->element(6);
	//int item3 = bot->Item->element(6, 1);

	//playerhealth::registrate_health(playerID, 100, (item == 211 || item2 == 211) ? 2 : 1);
	playerhealth::registrate_health(playerID, 100, item == 211 ? 2 : 1);
	recvspawn_o(_this, buffer, len);
}
void hkRecvDamageHelmet(uintptr _this, tarray* buffer, int len) {
	uintptr bufferptr = (uintptr)&buffer->array;

	int attackerID = *((unsigned char*)(bufferptr + 4));
	int victimID = *((unsigned char*)(bufferptr + 5));
	int attachmetID = *((unsigned char*)(bufferptr + 6));

	if(attachmetID == 211)
		playerhealth::registrate_health(victimID, -666, 1);

	recvdamagehelmet_o(_this, buffer, len);
}