#include "pch.h"
#include "Application.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Log.h"
#include "Platform/Windows/Win32_Window.h"

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
		b = std::make_unique<Box>(wnd->Gfx());

	} 


	Application::~Application()
	{
	}

	void Application::Run()
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


			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();


			m_Window->OnUpdate(m_Running);

			b->SetMatrix(
				DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
				DirectX::XMMatrixTranslation(0.0f - 4.0f, 0.0f, 20.0f)
			);
			b->Draw(wnd->Gfx());

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