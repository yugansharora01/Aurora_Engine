#pragma once

#include "Core.h"
#include "Window.h"
#include "Aurora/LayerStack.h"
#include "Aurora/Events/Events.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Imgui/ImguiLayer.h"


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

		static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline Ref<Window> GetWindowptr() { return m_Window; }

		bool IsSetupDone = false;
	public:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		
		bool m_Running = true;

		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	//To be defined in client
	Application* CreateApplication();

}