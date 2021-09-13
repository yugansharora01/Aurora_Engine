#pragma once

#include "Core.h"
#include "Window.h"
#include "Aurora/LayerStack.h"
#include "Events/Events.h"


namespace Aurora {

	class AURORA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

	};

	//To be defined in client
	Application* CreateApplication();

}