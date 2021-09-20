#include "pch.h"
#include "Application.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Log.h"
#include "Platform/Windows/Win32_Window.h"

namespace Aurora {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AU_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = Window::Create();

		auto wnd = (Win32_Window*)m_Window->GetNativeWindow();
		//b = std::make_unique<Box>(wnd->Gfx());

	} 


	Application::~Application()
	{
	}

	void Application::Run()
	{
		float i = 0.0f;
		float inc = 0.01f;
		while (m_Running)
		{
			if (i > 1.0f || i < 0.0f)
			{
				inc = -inc;
			} 

			i = i + inc;

			auto wnd = (Win32_Window*)m_Window->GetNativeWindow();
			wnd->Gfx().ClearBuffer(i, 0.08f, 0.9f);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate(m_Running);

			//b->Draw(wnd->Gfx());

			wnd->Gfx().EndFrame();
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