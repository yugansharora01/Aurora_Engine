#include "pch.h"
#include "Application.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Log.h"
#include "Platform/Windows/Win32_Window.h"
#include "Platform/Windows/AuroraException.h"
#include "Aurora/Renderer/FrameBuffer.h"

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
		m_Window->Gfx()->fbuf = FrameBuffer::Create(800, 600);

		for (Layer* layer : m_LayerStack)
			layer->Init();

		try
		{
			float i = 0.0f;
			float j = 0.0f;
			float k = 0.0f;

			while (m_Running)
			{
				m_Window->Gfx()->ClearBuffer(i, j,k);

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

	void Application::Close()
	{
		m_Running = false;
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