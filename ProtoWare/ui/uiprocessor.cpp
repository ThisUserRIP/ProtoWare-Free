#include "pch.h"
#include "uiprocessor.h"
#include "uirender.h"
#include "uimainfont.h"

#include "minhook.h"
#include "globals.h"

#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

typedef void(__fastcall* DELEGATE_UnityPresent)(uintptr gfxdevice);
typedef uintptr(__fastcall* DELEGATE_UnityGetPresent)();

DELEGATE_UnityPresent unitypresent_o;
DELEGATE_UnityGetPresent unitygetpresent_o;

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

bool hkpresent_init = false;
HRESULT __fastcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!hkpresent_init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ImGui::GetIO().Fonts->AddFontFromMemoryTTF(proggy_clean_13_ru, sizeof(proggy_clean_13_ru), 13, 0, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			hkpresent_init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	uirender::draw();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

void uiprocessor::initialize() {

	/*HMODULE overlayrenderer = GetModuleHandleA("GameOverlayRenderer64.dll");
	if (!overlayrenderer)
		exit(0);
	uintptr_t* Steam_DXGI_PresentScene = (uintptr_t*)((uintptr_t)overlayrenderer + 0x162258);
	oPresent = (Present)*Steam_DXGI_PresentScene;
	Steam_DXGI_PresentScene[0] = (uintptr_t)hkPresent;*/

	while (true) {
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			return;
		}
	}
}