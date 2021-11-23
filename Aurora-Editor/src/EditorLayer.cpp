#include "Editorpch.h"
#include <Aurora.h>
#include "EditorLayer.h"
#include "imgui.h"
#include "Aurora/Utils/Util.h"

namespace Aurora {

	void EditorLayer::Panels()
	{
		//To get the upper Left corner
		lastwindowposition = GetDisplayCoord();

		static ImVec4 color = {};

		ImGui::SetNextWindowPos(ImVec2((float)lastwindowposition[0], (float)lastwindowposition[1]), ImGuiCond_Once);

		lastwindowposition[2] -= lastwindowposition[0];       //Full screen width
		lastwindowposition[2] /= 5;                          //20% of full width
		lastwindowposition[3] = 150;

		ImGui::SetNextWindowSize(ImVec2(lastwindowposition[3], lastwindowposition[3]), ImGuiCond_Once);

		ImGui::Begin("Background Colors");
		ImGui::SliderFloat("Red", &red, 0.0f, 1.0f);
		ImGui::SliderFloat("Blue", &blue, 0.0f, 1.0f);
		ImGui::SliderFloat("Green", &green, 0.0f, 1.0f);

		color.x = red;
		color.y = green;
		color.z = blue;

		ImGui::ColorEdit3("color", (float*)&color);

		red = color.x;
		green = color.y;
		blue = color.z;

		ImGui::End();

		//-------------------------------------------------

		ImGui::Begin("Viewport");

		//ImGui::Image(fBuffer->GetBufferAsTexture(), ImVec2(300, 300));


		ImGui::End();
		//-------------------------------------------------
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
		bool docking = false;
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

	void EditorLayer::OnAttach()
	{
		//fBuffer = FrameBuffer::Create(800,600);
	}
}