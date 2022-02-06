#include "Editorpch.h"
#include "GeometryPanel.h"
#include "imgui.h"
#include "Aurora/Scene/Components.h"

namespace Aurora 
{
	void GeometryPanel::OnImGuiRender()
	{
		bool clicked = false;

		ImVec2 buttonSize = { 50.0f,30.0f };

		ImGui::Begin("Geometry Panel");

		if (ImGui::Button("Box", buttonSize))
		{
			clicked = true;
		}

		if (ImGui::Button("Sphere", buttonSize))
		{
			clicked = true;
		}

		if (ImGui::Button("Plane", buttonSize))
		{;
			clicked = true;
		}

		if (ImGui::Button("Cone", buttonSize))
		{
			clicked = true;
		}

		ImGui::End();

		if (clicked)
			DrawGeometry();
	}

	void GeometryPanel::DrawGeometry()
	{
		auto e = m_scene->CreateEntity();
		e->AddComponent<TransformComponent>(DirectX::XMFLOAT3(2.0f, 0.0f, 20.0f));
	}
}