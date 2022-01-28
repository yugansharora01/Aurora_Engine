#include "pch.h"
#include "Application.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Platform/Windows/Win32_Window.h"
#include "Platform/Windows/AuroraException.h"
#include "Aurora/Renderer/RenderTargetManager.h"

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
		
		IsSetupDone = true;
	} 


	Application::~Application()
	{
		m_Window->Close();
	}

	void Application::Run()
	{
		m_Window->Gfx()->TargetManager = RenderTargetManager::Create(800, 600);
		
		for (Layer* layer : m_LayerStack)
			layer->Init();

		try
		{
			while (m_Running)
			{
				
				m_Window->Gfx()->TargetManager->Clear(0.0f, 0.0f, 0.0f);
				if (m_Window->Gfx()->TargetManager->GetNumberOfTargets() != 0)
				{
					m_Window->Gfx()->TargetManager->BindTargets();
				}

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				m_ImGuiLayer->Begin();

				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}

				m_ImGuiLayer->End();

				m_Window->OnUpdate(m_Running);

				m_Window->Gfx()->EndFrame();
			}
		}
		catch (const AuroraException& e)
		{
			AU_CORE_FATAL("{0} \n{1}", e.GetType(), e.what());
		}
		catch (const std::exception& e)
		{
			AU_CORE_FATAL("{0}\n Standard Exception", e.what());
		}
		catch (...)
		{
			AU_CORE_FATAL("Unknown Exception \nNo Details Available");
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(AURORA_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(AURORA_BIND_EVENT_FN(Application::OnWindowResize));


		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		
		if (Application::Get().IsSetupDone)
		{
			m_Window->SetWindowData(e.GetWidth(), e.GetHeight());
			m_Window->Gfx()->Resize(e.GetWidth(), e.GetHeight());
			m_Window->Gfx()->TargetManager->Resize(e.GetWidth(), e.GetHeight());
			return true;
		}
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}