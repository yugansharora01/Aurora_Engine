#include "pch.h"
#include "Application.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Log.h"
#include "Platform/Windows/Win32_Window.h"
#include "Platform/Windows/AuroraException.h"

#include "imgui.h"

namespace Aurora {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AU_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = Window::Create();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_EditorLayer = new EditorLayer();
		PushOverlay(m_EditorLayer);

		auto wnd = (Win32_Window*)m_Window->GetNativeWindow();

		wnd->Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

	} 


	Application::~Application()
	{
	}

	void Application::Run()
	{
		try
		{
			float i = 0.0f;
			float inc = 0.01f;
			float inc1 = 0.01f;

			while (m_Running)
			{
				m_EditorLayer->Get(i,inc,inc1);

				auto wnd = (Win32_Window*)m_Window->GetNativeWindow();
				wnd->Gfx().ClearBuffer(i, inc, inc1);

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				m_EditorLayer->GetPos(i,inc,inc1);
				

				m_ImGuiLayer->Begin();

				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}

				m_ImGuiLayer->End();

				m_Window->OnUpdate(m_Running);


				wnd->Gfx().EndFrame();
			}
		}
		catch (const AuroraException& e)
		{
			AU_CORE_FATAL("{0}", e.what());
			MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
		}
		catch (const std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		}
		catch (...)
		{
			MessageBoxA(nullptr, "No Details Available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
		}
	}

	void Application::OnEvent(Event& e)
	{
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); it++)
		{
			(*--it)->OnEvent(e);
			if (e.m_handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

}