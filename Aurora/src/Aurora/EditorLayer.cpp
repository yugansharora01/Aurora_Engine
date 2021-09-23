#include "pch.h"
#include "EditorLayer.h"
#include "imgui.h"

namespace Aurora {
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
		static ImVec4 color = {};

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

		ImGui::Begin("Pos");
		ImGui::SliderFloat("x", &x, -100.0f, 100.0f);
		ImGui::SliderFloat("y", &y, -100.0f, 100.0f);
		ImGui::SliderFloat("z", &z, -100.0f, 100.0f);
		ImGui::End();
	}
}