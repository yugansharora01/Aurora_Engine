#include "Editorpch.h"
#include <Aurora.h>
#include "EditorLayer.h"
#include "Aurora/Utils/PlatformUtil.h"
#include "Aurora/Scene/Serializer.h"
#include "Aurora/Utils/PlatformUtil.h"
#include "Aurora/Utils/FileOperations.h"
#include "ImGuizmo.h"
#include "Aurora/Text/Text.h"

#include <imgui.h>

namespace Aurora {


	EditorLayer::EditorLayer()
	{
		m_sceneHeirarchyPanel = CreateRef<SceneHierarchyPanel>();
		m_geometryPanel = CreateRef<GeometryPanel>();

		m_activeScene = CreateRef<Scene>("Test Scene");
		m_editorCamera = CreateRef<EditorCamera>(1.0f, 3.0f / 4.0f, 0.5f, 40.0f);
		
	}

	void EditorLayer::Panels()
	{
		
		m_sceneHeirarchyPanel->SetScene(m_activeScene);
		m_sceneHeirarchyPanel->OnImGuiRender();

		m_geometryPanel->SetScene(m_activeScene);
		m_geometryPanel->OnImGuiRender();

		//-------------------------------------------------
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		ImVec2 viewportPanelPos = ImGui::GetWindowPos();
		auto [xpos, ypos] = Application::Get().GetWindow().GetPos();
		m_ViewportPos = { viewportPanelPos.x - xpos, viewportPanelPos.y - ypos };
		

		//ImGui::Image((void*)TextTexture->GetShaderResource().Get(), ImVec2(m_ViewportSize.x, m_ViewportSize.y));
		ImGui::Image(TargetManager->GetTextureAsPointer("viewport"), ImVec2(m_ViewportSize.x, m_ViewportSize.y));

		//Guizmo
		Ref<Entity> selectedEntity = m_sceneHeirarchyPanel->GetSelectedEntity();
		if (selectedEntity && m_GuizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowWidth = ImGui::GetWindowWidth();
			float windowHeight = ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			//auto camera = m_activeScene->Camera;
			auto viewMat = DirectX::XMMatrixInverse(NULL,m_editorCamera->GetTransform());
			auto projMat = m_editorCamera->GetProjection();

			auto component = selectedEntity->GetComponent<TransformComponent>();
			auto transformMat = component->GetTransform();

			DirectX::XMFLOAT4X4 viewfloat; 
			DirectX::XMStoreFloat4x4(&viewfloat, viewMat);
			
			DirectX::XMFLOAT4X4 projfloat; 
			DirectX::XMStoreFloat4x4(&projfloat, projMat);
			
			DirectX::XMFLOAT4X4 transformfloat; 
			DirectX::XMStoreFloat4x4(&transformfloat, transformMat);

			auto Translate = component->translate;
			auto Rotation = component->rotation;
			auto Scale = component->scale;

			ImGuizmo::RecomposeMatrixFromComponents(&Translate.x, &Rotation.x, &Scale.x, &transformfloat._11);

			ImGuizmo::Manipulate(&viewfloat._11, &projfloat._11, (ImGuizmo::OPERATION)m_GuizmoType, ImGuizmo::MODE::LOCAL, &transformfloat._11);
			
			if (ImGuizmo::IsUsing())
			{
				transformMat = DirectX::XMLoadFloat4x4(&transformfloat);

				ImGuizmo::DecomposeMatrixToComponents(&transformfloat._11, &component->translate.x, &Rotation.x, &component->scale.x);
				
				DirectX::XMFLOAT4 delta;

				delta.x = Rotation.x - component->rotation.x;
				delta.y = Rotation.y - component->rotation.y;
				delta.z = Rotation.z - component->rotation.z;

				component->rotation.x += delta.x;
				component->rotation.y += delta.y;
				component->rotation.z += delta.z;

			}
		}

		ImGui::End();
		ImGui::PopStyleVar();
		//-------------------------------------------------

	}

	void EditorLayer::OnImGuiRender()
	{
		bool docking = true;

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

				if (ImGui::MenuItem("New", "Ctrl+N", false, dockspaceOpen != NULL))
				{
					NewScene();
					
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O", false, dockspaceOpen != NULL))
				{
					OpenScene();
					
				}

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false, dockspaceOpen != NULL))
				{
					SaveSceneAs();
				}
				
				
				if (ImGui::MenuItem("Exit", "Esc", false, dockspaceOpen != NULL))
				{
					WindowCloseEvent e;
					Application::Get().OnWindowClose(e);
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		Panels();
			

		ImGui::End();
		
	}

	void EditorLayer::OnUpdate()
	{
		viewportInfo v;
		v.viewportSize = m_ViewportSize;
		v.viewportPos = m_ViewportPos;
		m_activeScene->Update(m_editorCamera,v);
	}

	void EditorLayer::OnAttach()
	{
		
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_editorCamera->OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(AURORA_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	void EditorLayer::Init()
	{
		
		//Text t;
		//TextTexture = t.get();
		TargetManager = Application::Get().GetWindow().Gfx()->TargetManager;

		RenderTargetProperties property;
		property.Width = 0;
		property.Height = 0;
		property.IsCPUAccessable = false;
		property.NumberOfTargets = 1;
		property.Format.IsNormalised = false;
		property.Format.NumberOfBits = 32;
		property.Format.type = PropertiesDataType::Float4;
		property.IsDataAccessable = true;

		TargetManager->AddRenderTarget("viewport", property);

		/*property.Format.type = PropertiesDataType::Float;
		property.Format.NumberOfBits = 32;

		TargetManager->AddRenderTarget("Mouse-Pick", property);*/

		auto NanoSuit = m_activeScene->CreateEntity("Mesh1");

		NanoSuit->AddComponent<TransformComponent>(DirectX::XMFLOAT3(0.0f, -10.0f, 20.0f), DirectX::XMFLOAT3(0.0f, 3.14f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
		//NanoSuit->AddComponent<MeshComponent>(false,"assets\\models\\cube\\Wooden Crate\\Wooden Crate.obj");
		NanoSuit->AddComponent<MeshComponent>(false,"assets\\models\\nano_textured\\nanosuit.obj");
		auto c2 = NanoSuit->GetComponent<MeshComponent>();
		c2->color = { 0.3f,0.0f,0.3f,1.0f };
		//c2->SetTexture(c2->path);


		auto Light = m_activeScene->CreateEntity("Light1");

		Light->AddComponent<TransformComponent>(DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f));
		Light->AddComponent<MeshComponent>(false,"assets\\models\\cube\\Wooden Crate\\Wooden Crate.obj");
		Light->AddComponent<LightComponent>();

		//auto Text = m_activeScene->CreateEntity("Text");

		//auto TextComp = Text->AddComponent<TextComponent>();
		//TextComp->Text = "LOL";
		
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		bool control = Input::IsKeyPressed(Key::Control);
		bool shift = Input::IsKeyPressed(Key::Shift);

		switch (e.GetKeyCode())
		{
		case Key::N:
		{
			if (control)
				NewScene();
			break;
		}

		case Key::O:
		{
			if (control)
				OpenScene();
			break;
		}

		case Key::S:
		{
			if (control && shift)
				SaveSceneAs();
			break;
		}

		case Key::Escape:
		{
			WindowCloseEvent e;
			Application::Get().OnWindowClose(e);
			break;
		}

		//Guizmo
		case Key::Q:
		{
			if (!ImGuizmo::IsUsing())
				m_GuizmoType = -1;
			break;
		}
		
		case Key::W:
		{
			if (!ImGuizmo::IsUsing() && control)
				m_GuizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		}
		
		case Key::E:
		{
			if (!ImGuizmo::IsUsing() && control)
				m_GuizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		}
		
		case Key::R:
		{
			if (!ImGuizmo::IsUsing() && control)
				m_GuizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}

		default:
			break;
		}
		return false;
	}


	void EditorLayer::NewScene()
	{
		m_activeScene = CreateRef<Scene>();
	}

	void EditorLayer::OpenScene()
	{
		std::string filePath = FileDialog::OpenFile("Aurora Scene (*.Aurora)\0*.Aurora\0");
		if (!filePath.empty())
		{
			OpenScene(filePath);
		}
	}

	void EditorLayer::OpenScene(const std::filesystem::path& filePath)
	{
		m_activeScene = CreateRef<Scene>();
		Serializer serializer(m_activeScene);
		serializer.Deserialize(filePath.string());
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filePath = FileDialog::SaveFile("Aurora Scene (*.Aurora)\0*.Aurora\0");

		if (!filePath.empty())
		{
			Serializer serializer(m_activeScene);
			serializer.Serialize(filePath);
		}
	}
}