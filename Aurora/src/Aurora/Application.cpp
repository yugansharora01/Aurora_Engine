#include "pch.h"
#include "Application.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Log.h"

namespace Aurora {


	Application::Application()
	{
		m_Window = Window::Create();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		//WindowResizeEvent e(1200, 720);
		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	AU_TRACE(e);
		//}
		//if (e.IsInCategory(EventCategoryInput))
		//{
		//	AU_TRACE(e);
		//}
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate(m_Running);
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
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

}