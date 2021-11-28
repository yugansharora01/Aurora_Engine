#include "Editorpch.h"
#include <Aurora.h>
#include "EditorLayer.h"
#include "imgui.h"
#include "Aurora/Utils/Util.h"

namespace Aurora {


	EditorLayer::EditorLayer()
	{
		color = {};
		color.w = 1.0f;

		DirectX::XMFLOAT3 pos;

		const auto model = Cube::Make<DirectX::XMFLOAT3>();

		vBuf = VertexBuffer::Create(model.vertices);

		vShader = VertexShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexVS.cso");

		pShader = PixelShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexPS.cso");

		iBuf = IndexBuffer::Create(model.indices);

		std::array<DirectX::XMFLOAT4, 8> face_colors =
		{
			{
				{ 1.0f,1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f,1.0f },
				{ 0.0f,1.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f,1.0f },
				{ 0.0f,0.0f,1.0f,1.0f },
				{ 1.0f,0.0f,1.0f,1.0f },
				{ 0.0f,1.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f,1.0f },
			}
		};
		pShader->UploadMat4X8(face_colors);

		std::vector<LayoutBuffer> list;

		list.emplace_back("Position", 0u, ShaderDataType::Float3, false, 32);


		vBuf->SetLayout(list, vShader);

		vBuf->SetTopology(TopologyType::Triangle_List);

		m_camera = std::make_shared<EditorCamera>(1, 3.0f / 4.0f, 0.5f, 40.0f);
	}

	void EditorLayer::Panels()
	{
		//To get the upper Left corner
		//lastwindowposition = GetDisplayCoord();


		//ImGui::SetNextWindowPos(ImVec2((float)lastwindowposition[0], (float)lastwindowposition[1]), ImGuiCond_Once);

		//lastwindowposition[2] -= lastwindowposition[0];       //Full screen width
		//lastwindowposition[2] /= 5;                          //20% of full width
		//lastwindowposition[3] = 150;

		//ImGui::SetNextWindowSize(ImVec2(lastwindowposition[3], lastwindowposition[3]), ImGuiCond_Once);

		

		ImGui::Begin("Background Colors");
		ImGui::SliderFloat("Red", &color.x, 0.0f, 1.0f);
		ImGui::SliderFloat("Green", &color.y, 0.0f, 1.0f);
		ImGui::SliderFloat("Blue", &color.z, 0.0f, 1.0f);
		ImGui::SliderFloat("alpha", &color.w, 0.0f, 1.0f);


		ImGui::ColorEdit4("color", &color.x);

		ImGui::End();

		//-------------------------------------------------

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		Application::Get().GetWindow().Gfx()->ClearBuffer(color.x, color.y, color.z);
		//fBuffer->Clear(color.x,color.y,color.z,color.w);
		ImGui::Image(fBuffer->GetBufferAsTexture(), ImVec2(m_ViewportSize.x, m_ViewportSize.y));

		ImGui::End();
		//-------------------------------------------------

		OnUpdate();
	}
	

	void EditorLayer::OnImGuiRender()
	{
		bool docking = true;
		if (docking)
		{
			static bool dockspaceOpen = true;

			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			else
			{
				//ShowDockingDisabledMessage();
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{

					if (ImGui::MenuItem("Exit", NULL, false, dockspaceOpen != NULL))
					{
						Application::Get().Close();
					}

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			Panels();
			

			ImGui::End();
		}
		else {
			Panels();
		}
	}

	void EditorLayer::OnUpdate()
	{
		auto height = Application::Get().GetWindow().GetHeight();
		auto width = Application::Get().GetWindow().GetWidth();
		m_camera->UpdateProjection(1, (float)height / (float)width, 0.5f, 40.0f);


		vShader->UploadMat4(DirectX::XMMatrixTranspose(
			GetMatrix() * m_camera->GetProjection()));

		//pShader->UploadMat4X8(GetColor());

		Renderer::BeginScene();

		Renderer::Submit(vShader, pShader, vBuf, iBuf);

		Renderer::EndScene();
	}

	void EditorLayer::OnAttach()
	{
		fBuffer = Graphics::fbuf;
	}
	DirectX::XMMATRIX EditorLayer::GetMatrix()
	{
		return DirectX::XMMatrixRotationRollPitchYaw(x1, y1, z1) *
			DirectX::XMMatrixTranslation(x, y, z);
	}
}