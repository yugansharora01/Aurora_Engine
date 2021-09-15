#include "pch.h"
#include "ImguiLayer.h"

#include "imgui.h"
#include "Platform/DirectX/imgui_impl_dx11.h"
#include <backends/imgui_impl_win32.h>
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {

	ImguiLayer::ImguiLayer()
		:Layer("ImguiLayer")
	{
	}

	ImguiLayer::~ImguiLayer()
	{
	}

	void ImguiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

		io.KeyMap[ImGuiKey_Tab] = VK_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
		io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
		io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
		io.KeyMap[ImGuiKey_Home] = VK_HOME;
		io.KeyMap[ImGuiKey_End] = VK_END;
		io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
		io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
		io.KeyMap[ImGuiKey_Space] = VK_SPACE;
		io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
		io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
		io.KeyMap[ImGuiKey_A] = 'A';
		io.KeyMap[ImGuiKey_C] = 'C';
		io.KeyMap[ImGuiKey_V] = 'V';
		io.KeyMap[ImGuiKey_X] = 'X';
		io.KeyMap[ImGuiKey_Y] = 'Y';
		io.KeyMap[ImGuiKey_Z] = 'Z';

		auto wnd = (Win32_Window*)Application::Get().GetWindow().GetNativeWindow();

		//ImGui_ImplWin32_Init(wnd->GetHandle());
		ImGui_ImplDX11_Init(wnd->Gfx().GetDevice().Get(), wnd->Gfx().GetContext().Get());
	}

	void ImguiLayer::OnDetach()
	{
	}

	void ImguiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetHeight(), app.GetWindow().GetWidth());

		float time = timer.Peek();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplDX11_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnEvent(Event& event)
	{
	}
}


/////////16:00 ImGui
