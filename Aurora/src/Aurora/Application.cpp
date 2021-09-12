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
			m_Window->OnUpdate(m_Running);
		}
	}

}