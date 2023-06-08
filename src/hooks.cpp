#include "hooks.h"
#include <intrin.h>
#include "../include/MinHook/MinHook.h"
// individual hooks
#include "hooks/DX9.h"
#include "gui/gui.h"
#include "hooks/createmove.h"

void hooks::Setup() {
	MH_Initialize();

	gui::Setup();
	hooks::ImGui::Setup();
	hooks::createmove::Setup();

	MH_EnableHook(MH_ALL_HOOKS);
}

void hooks::Destroy() noexcept {
	gui::Destroy();
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}