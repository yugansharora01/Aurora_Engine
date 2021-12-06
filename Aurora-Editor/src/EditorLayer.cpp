#include "Editorpch.h"
#include <Aurora.h>
#include "EditorLayer.h"
#include "imgui.h"
#include "Aurora/Utils/Util.h"

namespace Aurora {


	EditorLayer::EditorLayer()
	{
		m_sceneHeirarchyPanel = CreateRef<SceneHierarchyPanel>();

		m_activeScene = CreateRef<Scene>();

		std::wstring vShaderpath(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexVS.cso");
		std::wstring pShaderpath(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexPS.cso");

		/*auto e = m_activeScene->CreateEntity("Box");

		e->AddComponent<TransformComponent>();
		e->AddComponent<MeshComponent>(vShader,pShader,vBuf,iBuf);

		auto e1 = m_activeScene->CreateEntity("Box1");

		auto t = DirectX::XMFLOAT3(4.0f, 0.0f, 20.0f);

		e1->AddComponent<TransformComponent>(t);
		e1->AddComponent<MeshComponent>(vertexShader, pixelShader, vertexBuf, indexBuf);
		*/
		auto cube = Cube::Get(vShaderpath,pShaderpath );

		auto e2 = m_activeScene->CreateEntity("Box1");

		auto t1 = DirectX::XMFLOAT3(2.0f, 0.0f, 20.0f);

		e2->AddComponent<TransformComponent>(t1);
		e2->AddComponent<MeshComponent>(cube.vShader, cube.pShader, cube.vBuffer, cube.iBuffer);

	}

	void EditorLayer::Panels()
	{
		
		auto e = m_activeScene->registry->GetList()[0]->GetComponent<TransformComponent>();

		m_sceneHeirarchyPanel->SetScene(m_activeScene);
		m_sceneHeirarchyPanel->OnImGuiRender();


		//-------------------------------------------------

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		ImGui::Image(fBuffer->GetBufferAsTexture(), ImVec2(m_ViewportSize.x, m_ViewportSize.y));

		ImGui::End();
		//-------------------------------------------------

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
		m_activeScene->Update();
	}

	void EditorLayer::OnAttach()
	{
		fBuffer = Graphics::fbuf;
	}
	
}