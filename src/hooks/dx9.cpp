#include "DX9.h"

#include <stdexcept>
#include <intrin.h>

#include "../../include/MinHook/MinHook.h"

#include "../../include/ImGui/imgui.h"
#include "../../include/ImGui/imgui_impl_win32.h"
#include "../../include/ImGui/imgui_impl_dx9.h"	

void hooks::ImGui::Setup()
{
	if (MH_CreateHook(
		VirtualFunction(gui::device, 42),
		&EndScene,
		reinterpret_cast<void**>(&EndSceneOriginal)
	)) throw std::runtime_error("Unable to hook EndScene()");

	if (MH_CreateHook(
		VirtualFunction(gui::device, 16),
		&EndScene,
		reinterpret_cast<void**>(&ResetOriginal)
	)) throw std::runtime_error("Unable to hook Reset()");

	gui::DestroyDirectX();
}

long __stdcall hooks::ImGui::EndScene(IDirect3DDevice9* device) noexcept
{
    static const auto returnAddress = _ReturnAddress();

    const auto result = EndSceneOriginal(device, device);

    // stop endscene getting called twice
    if (_ReturnAddress() == returnAddress)
        return result;

    if (!gui::setup)
        gui::SetupMenu(device);

    device->GetRenderState(D3DRS_COLORWRITEENABLE, &old_color_write);
    device->GetRenderState(D3DRS_SRGBWRITEENABLE, &old_srgb_write);
    device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
    device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

    if (gui::open)
        gui::Render();

    device->SetRenderState(D3DRS_COLORWRITEENABLE, old_color_write);
    device->SetRenderState(D3DRS_SRGBWRITEENABLE, old_srgb_write);

    return result;
}

HRESULT __stdcall hooks::ImGui::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}
