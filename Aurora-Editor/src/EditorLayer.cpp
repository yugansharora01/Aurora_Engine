#include "EditorLayer.h"
#include "imgui.h"
#include "Aurora/Utils/Util.h"

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
		

		//To get the upper Left corner
		lastwindowposition = GetDisplayCoord();

		static ImVec4 color = {};

		ImGui::SetNextWindowPos(ImVec2((float)lastwindowposition[0], (float)lastwindowposition[1]),ImGuiCond_Once);
		
		lastwindowposition[2] -= lastwindowposition[0];       //Full screen width
		lastwindowposition[2] /= 5;                          //20% of full width
		lastwindowposition[3] = 150;
		
		ImGui::SetNextWindowSize(ImVec2(lastwindowposition[3], lastwindowposition[3]),ImGuiCond_Once);

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