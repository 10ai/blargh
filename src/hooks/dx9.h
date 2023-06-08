#pragma once
#include "../gui/gui.h"
#include "../hooks.h"

namespace hooks::ImGui
{
	void Setup();

	constexpr void* VirtualFunction(void* thisptr, size_t index) noexcept
	{
		return(*static_cast<void***>(thisptr))[index];
	}

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFn EndSceneOriginal = nullptr;
	long __stdcall EndScene(IDirect3DDevice9* device) noexcept;

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;

	inline DWORD old_color_write, old_srgb_write;
}