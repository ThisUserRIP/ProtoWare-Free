#include "pch.h"
#include "game.h"
#include "globals.h"
#include "uiprocessor.h"
#include "minhook.h"

#include "aim.h"
#include "visuals.h"
#include "movement.h"
#include "target_system.h"
#include "updatecycle.h"
#include "killfeed.h"
#include "hitnotify.h"
#include "custom_attack.h"
#include "playerhealth.h"
#include "fast_raycast.h"

auto Addres_oWRITE_LONG = reinterpret_cast<DWORD_PTR>(GetModuleHandleA("GameAssembly")) + 0x56FBE0;

typedef void(*t_WRITE_LONG)(Client*, int32_t);
inline t_WRITE_LONG oWRITE_LONG;

void hWRITE_LONG(Client* _this, int32_t value) {
    if (value == 11427 || value == 11431)
        value = 11327;

    oWRITE_LONG(_this, value);
}

void MainThread() {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

    gameassembly = (uintptr)GetModuleHandleA("GameAssembly.dll");
    if (!gameassembly) {
        std::cout << "[!] Failed to get GameAssembly.dll" << std::endl;
        return;
    }

    unityplayer = (uintptr)GetModuleHandleA("UnityPlayer.dll");
    printf("GameAssembly: %p\n", gameassembly);
    printf("UnityPlayer: %p\n", unityplayer);

    MH_Initialize();

    MH_CreateHook((void*)(Addres_oWRITE_LONG), &hWRITE_LONG, reinterpret_cast<void**>(&oWRITE_LONG));
    MH_EnableHook((void*)(Addres_oWRITE_LONG));

    game::initialize();
    uiprocessor::initialize();
    aim::initialize();
    visuals::initialize();
    movement::initialize();
    target_system::initialize();
    updatecycle::initialize();
    killfeed::initialize();
    hitnotify::initialize();
    custom_attack::initialize();
    playerhealth::initialize();
    fast_raycast::initialize();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return 1;
    
    DisableThreadLibraryCalls(hModule);
    simple_thread(MainThread, 8192 * 4);
    return 1;
}

