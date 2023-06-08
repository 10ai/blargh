#include "createmove.h"

#include <intrin.h>
#include <stdexcept>
#include <sstream>
#include <cstdint>
#include <iostream> 
#include <format>
#include <iostream>
#include <bitset>
#include <string>
#include <string_view>
#include "../../include/MinHook/MinHook.h"
#include "../gui/windows/tasmenu.h"
#include "../features/playbackcsstas.h"

bool print;

void hooks::createmove::Setup() 
{
    g_Client = GetInterface<void>("VClient017", "client.dll");

    g_ClientMode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(g_Client))[10] + 5);

    if (MH_CreateHook(
        (*static_cast<void***>(g_ClientMode))[21],
        &CreateMoveHook,
        reinterpret_cast<void**>(&CreateMoveOriginal)
    )) throw std::runtime_error("Failed to hook CreateMove()!");
}

template <typename T>
static T* hooks::createmove::GetInterface(const char* name, const char* library)
{
    const HINSTANCE handle = GetModuleHandle(library);

    if (!handle)
        return nullptr;

    using Fn = T * (*)(const char*, int*);
    const Fn CreateInterface = reinterpret_cast<Fn>(GetProcAddress(handle, "CreateInterface"));

    return CreateInterface(name, nullptr);
}

bool __fastcall hooks::createmove::CreateMoveHook(void* _this, void* edx, float frameTime, CUserCmd* cmd)
{
    const bool result = CreateMoveOriginal(g_ClientMode, frameTime, cmd);
    
    if (!cmd->command_number)
        return false;

    std::string string;
    string += std::format("frametime: {}\n", frameTime);
    string += std::format("forwardmove: {}\n", cmd->forwardmove);
    string += std::format("sidemove: {}\n", cmd->sidemove);
    string += std::format("buttons: {}\n", std::bitset<16>(cmd->buttons).to_string());
    string += std::format("viewangles: ({}, {})\n", cmd->viewangles.x, cmd->viewangles.y);

    tasmenu::createmove = string;

    tasmenu::CurrentFrame(cmd);

    return result;
}