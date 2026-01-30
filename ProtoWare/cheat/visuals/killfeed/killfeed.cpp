#include "pch.h"
#include "killfeed.h"

#include "component.h";
#include "internal_component.h";
#include "internal_transform.h";
#include "internal_gameobject.h";

#include "gameoffsets.h"
#include "game.h"
#include "globals.h"
#include "minhook.h"
#include "tarray.h"
#include "monostring.h"
#include "hitnotify.h"
#include "playerhealth.h"

#include "stClient.hpp"
#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"

typedef bool(__fastcall* DELEGATE_RecvDamage)(Client* _this, tarray* buffer, int len);

DELEGATE_RecvDamage recvdamage_o;
char killfeed__monostring_buf[128];

void hkRecvDamage(Client* _this, tarray* buffer, int len);
char* killfeed__transform_monostring(monostring* str) {
	WideCharToMultiByte(CP_UTF8, 0, str->wstring, -1, killfeed__monostring_buf, 128, 0, 0);
	return killfeed__monostring_buf;
}

void killfeed::initialize() {
	MH_CreateHook((void*)(gameassembly + client_recvdamage_method_offset), &hkRecvDamage, (void**)&recvdamage_o);
	MH_EnableHook((void*)(gameassembly + client_recvdamage_method_offset));
}

void hkRecvDamage(Client* _this, tarray* buffer, int len) {

	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller || !pcontroller->RemotePlayersList) return;

	tarray* players = pcontroller->RemotePlayersList;

	uintptr bufferptr = (uintptr)&buffer->array;

	int attackerID = *((unsigned char*)(bufferptr + 4));
	int victimID = *((unsigned char*)(bufferptr + 5));
	int health = *((int*)(bufferptr + 6));
	int weaponID = *((int*)(bufferptr + 10));
	int hitzone = *((unsigned char*)(bufferptr + 14));

	playerhealth::registrate_health(victimID, health, 0);
	if (health == 0) {
		//if (attackerID == _this->myindex) {
		//	printf("you are killed the %s\n", nick);
		//} 
		//else printf("killed %s\n", nick);
		if (attackerID == _this->myindex) {
			internal_transform* ownTrs = ((internal_component*)_this->__internalObj)->gameobject->get_transform();

			ServerBotData* victimBot = (ServerBotData*)players->element(victimID);

			component* botposer = (component*)victimBot->botPoser;
			if (!botposer->internal_component) goto RET;
			internal_transform* transform = botposer->internal_component->gameobject->get_transform();
			vec3 position = transform->get_kernel_pos();

			char* nick = killfeed__transform_monostring(victimBot->Name);
			printf("you are killed the %s\n", nick);
			hitnotify::add_death(nick, ownTrs->get_kernel_pos().get_distance(position));
		} 
	}

	RET:
	recvdamage_o(_this, buffer, len);
}