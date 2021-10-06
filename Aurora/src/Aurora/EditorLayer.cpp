#include "pch.h"
#include "EditorLayer.h"
#include "imgui.h"

#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"


namespace Aurora {

	inline DirectX::XMINT4 GetDisplayCoord(const HWND hwnd)
	{
		RECT rect;

		GetWindowRect(hwnd, &rect);

		RECT wrect;
		GetWindowRect(hwnd, &wrect);
		RECT crect;
		GetClientRect(hwnd, &crect);
		POINT lefttop = { crect.left, crect.top }; // Practicaly both are 0
		ClientToScreen(hwnd, &lefttop);
		POINT rightbottom = { crect.right, crect.bottom };
		ClientToScreen(hwnd, &rightbottom);

		int left_border = lefttop.x - wrect.left; // Windows 10: includes transparent part
		int right_border = wrect.right - rightbottom.x; // As above
		int bottom_border = wrect.bottom - rightbottom.y; // As above
		int top_border_with_title_bar = lefttop.y - wrect.top; // There is no transparent part
		
		return { rect.left + left_border, rect.top + top_border_with_title_bar ,rect.right - right_border ,rect.bottom - bottom_border };
	}



	void EditorLayer::Get(float &Red, float &Green, float &Blue)
	{
		Red = red;
		Green = green;
		Blue = blue;
	}

	void EditorLayer::GetPos(float& x, float& y, float& z)
	{
		x = EditorLayer::x;
		y = EditorLayer::y;
		z = EditorLayer::z;
	}
	
	void EditorLayer::OnImGuiRender()
	{
		auto wnd = (Win32_Window*)Application::Get().GetWindow().GetNativeWindowPtr();

		//To get the upper Left corner
		lastwindowposition = GetDisplayCoord(wnd->GetHandle());

		static ImVec4 color = {};

		ImGui::SetNextWindowPos(ImVec2((float)lastwindowposition.x, (float)lastwindowposition.y),ImGuiCond_Once);
		
		lastwindowposition.z -= lastwindowposition.x;       //Full screen width
		lastwindowposition.z /= 5;                          //20% of full width
		lastwindowposition.w = 150;
		
		ImGui::SetNextWindowSize(ImVec2(lastwindowposition.z, lastwindowposition.w),ImGuiCond_Once);

		ImGui::Begin("Background Colors");
		ImGui::SliderFloat("Red", &red, 0.0f, 1.0f);
		ImGui::SliderFloat("Blue", &blue, 0.0f, 1.0f);
		ImGui::SliderFloat("Green", &green, 0.0f, 1.0f);

		color.x = red ;
		color.y = green;
		color.z = blue;

		ImGui::ColorEdit3("color", (float*)&color);

		red = color.x;
		green = color.y;
		blue = color.z;

		ImGui::End();

		

		//ImGui::SetNextWindowPos(ImVec2(lastwindowposition.x , lastwindowposition.y + lastwindowposition.w), ImGuiCond_Once);

		//ImGui::SetNextWindowSize(ImVec2(lastwindowposition.z, lastwindowposition.w), ImGuiCond_Once);


	}
}