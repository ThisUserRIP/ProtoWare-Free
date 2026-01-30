#pragma once
#include "monostring.h"

struct PlayerProfile {
	monostring* PlayerName; // 0x0
	monostring* session; // 0x8
	monostring* gameSession; // 0x10
	int country; // 0x18
	int __padding1;
	monostring* countrySTR; // 0x20
	bool dailyPost; // 0x28
	bool socialQuest; // 0x29
	char __padding2[2];
	int launcher; // 0x2c
	monostring* launcherID; // 0x30
	monostring* launcherAuthkey; // 0x38
	uintptr network; // 0x40
	monostring* id; // 0x48
	monostring* authkey; // 0x50
	int BannedTimeLeft; // 0x58
	bool CanUnban; // 0x5c
	bool NY2017Q; // 0x5d
	bool NY2018Q; // 0x5e
	bool VD2017Q; // 0x5f
	uintptr currentMission; // 0x60
	monostring* screenShotURL; // 0x68
	monostring* myInventory; // 0x70
	bool get_bonuses; // 0x78
	bool player_need_refresh; // 0x79
	char __padding3[2];
	int money; // 0x7c
	int moneypay; // 0x80
	int premium; // 0x84
	int exp; // 0x88
	int level; // 0x8c
	int skin; // 0x90
	int ha1; // 0x94
	int ha2; // 0x98
	int ha3; // 0x9c
	monostring* friends; // 0xa0
	monostring* friendServers; // 0xa8
	uintptr friendsOnline; // 0xb0
	uintptr friendsOnlineServers; // 0xb8
	uintptr friendsRating; // 0xc0
	int myindex; // 0xc8
	int myteam; // 0xcc
	int isAnimal; // 0xd0
	int jetpackFuel; // 0xd4
	uintptr crossList; // 0xd8
	uintptr crossDot; // 0xe0
	//Color crossColor; // 0xe8
	//Int32 currency; // 0xf8
	//Int32 reg_data; // 0xfc
	//String reg_data_parsed; // 0x100
};

