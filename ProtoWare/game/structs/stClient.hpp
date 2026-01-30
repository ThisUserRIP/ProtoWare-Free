#include "pch.h"
#include "il2cpp_structs.h"
#include "monostring.h"
#include "tarray.h"

#define IL2CPP_CLASS il2cpp_class*
#define IL2CPP_STRING monostring*
#define IL2CPP_ARRAY tarray*

struct Client {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	uintptr entManager; // 0x18
	int myindex; // 0x20
	int zs_wave; // 0x24
	uintptr client; // 0x28
	bool showEnetStat; // 0x30
	char padding_0[7];
	IL2CPP_STRING lastMessage; // 0x38
	uintptr LocalPlayer; // 0x40
	bool active; // 0x48
	bool ready_for_auth; // 0x49
	bool ready_for_disconnect; // 0x4a
	char padding_1[5];
	uintptr currentControlledVehicle; // 0x50
	uintptr goMap; // 0x58
	uintptr map; // 0x60
	uintptr ziploader; // 0x68
	uintptr csrm; // 0x70
	uintptr cspm; // 0x78
	uintptr Player; // 0x80
	uintptr cspc; // 0x88
	uintptr goGui; // 0x90
	uintptr csTeamScore; // 0x98
	uintptr Tlist; // 0xa0
	IL2CPP_ARRAY sendBuffer; // 0xa8, Byte[]
	IL2CPP_ARRAY readBuffer; // 0xb0, Byte[]
	int SplitRead; // 0xb8
	char padding_2[4];
	uintptr pos; // 0xc0
	IL2CPP_ARRAY net_stats_packet; // 0xc8, Int32[]
	IL2CPP_ARRAY net_stats_size; // 0xd0, Int32[]
	bool net_stats; // 0xd8
	char padding_3[7];
	IL2CPP_STRING load_msg1; // 0xe0
	IL2CPP_STRING load_msg2; // 0xe8
	float SingleTripTime; // 0xf0
	char padding_4[4];
	IL2CPP_ARRAY RECV_PACKETS; // 0xf8, RecvPacketDelegate[]
	int currentTime; // 0x100
	int clientTik; // 0x104
	int entityTik; // 0x108
	int latencyTik; // 0x10c
	float missions_timeout; // 0x110
	int mode; // 0x114
	uintptr MG; // 0x118
	int writepos; // 0x120
	char padding_5[4];
	unsigned __int64 lastLostPackets; // 0x128
	float lastLostPacketsTime; // 0x130
	char padding_6[4];
	IL2CPP_ARRAY decodeBuffer; // 0x138, Byte[]
	int readlen; // 0x140
	int readpos; // 0x144
	bool readerror; // 0x148
};