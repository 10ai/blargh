#pragma once
#include "../hooks.h"
#include "../../include/CUserCmd.h"

namespace hooks::createmove {

	static void* g_Client = nullptr;
	static void* g_ClientMode = nullptr;

	using CreateMove = bool(__thiscall*)(void*, float, CUserCmd*);
	static CreateMove CreateMoveOriginal = nullptr;

	void Setup();

	void TogglePrint();

	bool __fastcall CreateMoveHook(void* _this, void* edx, float frameTime, CUserCmd* cmd);

	template <typename T>
	static T* GetInterface(const char* name, const char* library);
}