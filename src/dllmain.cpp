// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <thread>

#include "hooks.h"

// Mr. Petersen
// If you are reading this
// I am so sorry lmfao
// This is such a mess

void Setup(const HMODULE hModule) noexcept 
{
    hooks::Setup();

    while (!GetAsyncKeyState(VK_END))
        Sleep(200);

    hooks::Destroy();

    FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 0);
}

BOOL APIENTRY DllMain( 
    const HMODULE hModule,
    const std::uintptr_t  ul_reason_for_call,
    const void* lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        const auto thread = CreateThread(
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup),
            hModule,
            0,
            nullptr
        );
        if (thread)
            CloseHandle(thread);
    }
    return TRUE;
}

