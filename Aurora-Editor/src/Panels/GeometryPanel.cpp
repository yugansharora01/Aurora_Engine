#include "Editorpch.h"
#include "GeometryPanel.h"
#include "imgui.h"
#include "Aurora/Drawables/Geometry/Geometry.h"
#include "Aurora/Scene/Components.h"

namespace Aurora 
{
	void GeometryPanel::OnImGuiRender()
	{
		std::wstring vShaderpath(L"../Aurora/src/Aurora/Shaders/PhongVS.hlsl");
		std::wstring pShaderpath(L"../Aurora/src/Aurora/Shaders/PhongPS.hlsl");

		std::wstring vShaderpath1(L"../Aurora/src/Aurora/Shaders/ColorIndexVS.hlsl");
		std::wstring pShaderpath1(L"../Aurora/src/Aurora/Shaders/ColorIndexPS.hlsl");

		bool clicked = false;

		ImVec2 buttonSize = { 50.0f,30.0f };

		ImGui::Begin("Geometry Panel");

		if (ImGui::Button("Box", buttonSize))
		{
			geometry = Cube::Get(vShaderpath, pShaderpath);
			clicked = true;
		}

		if (ImGui::Button("Sphere", buttonSize))
		{
			geometry = Sphere::Get(vShaderpath, pShaderpath,10,10);
			clicked = true;
		}

		if (ImGui::Button("Plane", buttonSize))
		{
			geometry = Plane::Get(vShaderpath, pShaderpath,10,10);
			clicked = true;
		}

		if (ImGui::Button("Cone", buttonSize))
		{
			geometry = Cone::Get(vShaderpath, pShaderpath,4);
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
		//e->AddComponent<MeshComponent>(geometry.vShader, geometry.pShader, geometry.vBuffer, geometry.iBuffer);
	}
}