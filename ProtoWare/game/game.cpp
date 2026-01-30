#include "pch.h"
#include "globals.h"

#include "il2cpp.h"
#include "il2cpp_structs.h"
#include "game.h"
#include "gameoffsets.h"

void game::initialize() {
	il2cpp::initialize_unity_class(gameassembly + server_players_controller_class_offset);
	il2cpp::initialize_unity_class(gameassembly + client_class_offset);
	il2cpp::initialize_unity_class(gameassembly + sendpacket_class_offset);
	il2cpp::initialize_unity_class(gameassembly + ziploader_class_offset);
	il2cpp::initialize_unity_class(gameassembly + gm_class_offset);
	il2cpp::initialize_unity_class(gameassembly + playerprofile_class_offset);
	il2cpp::initialize_unity_class(gameassembly + connectioninfo_class_offset);
	il2cpp::initialize_unity_class(gameassembly + const_class_offset);
	il2cpp::initialize_unity_class(gameassembly + scenemanager_class_offset);
	il2cpp::initialize_unity_class(gameassembly + map_class_offset);
}

ServerPlayersController* game::get_pcontroller() {
	return *(ServerPlayersController**)((*(il2cpp_class**)(gameassembly + server_players_controller_class_offset))->static_fields);
}
Client* game::get_client() {
	return *(Client**)((*(il2cpp_class**)(gameassembly + client_class_offset))->static_fields);
}
uintptr game::get_send_packet() {
	return *(uintptr*)((*(il2cpp_class**)(gameassembly + send_packet_damage_offset))->static_fields);
}
uintptr game::get_map() {
	return *(uintptr*)((*(il2cpp_class**)(gameassembly + map_class_offset))->static_fields);
}
uintptr game::get_packetcmds_fields() {
	return (uintptr)((*(il2cpp_class**)(gameassembly + sendpacket_class_offset))->static_fields);
}
PlayerProfile* game::get_profile() {
	return (PlayerProfile*)((*(il2cpp_class**)(gameassembly + playerprofile_class_offset))->static_fields);
}
E_MODE game::get_mode() {
	uintptr static_fields = (uintptr)(*(il2cpp_class**)(gameassembly + ziploader_class_offset))->static_fields;
	uintptr instance = *((uintptr*)(static_fields + ziploader_instance_offset));
	if (!instance) return E_MODE_NULL;
	int mode = *((int*)(instance + ziploader_gamemode_offset));
	return (E_MODE)mode;
}
E_GS game::get_gs() {
	uintptr static_fields = (uintptr)(*(il2cpp_class**)(gameassembly + gm_class_offset))->static_fields;
	int gs = *((int*)(static_fields + gm_currmainstate_offset));
	return (E_GS)gs;
}