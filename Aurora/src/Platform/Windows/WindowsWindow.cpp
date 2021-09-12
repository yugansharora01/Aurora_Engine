#include "pch.h"
#include "WindowsWindow.h"

namespace Aurora {

	static bool WindowInitialised = false;

	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate(bool &m_Running)
	{
		//TO DO
		if (const auto ecode = Win32_Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			//return *ecode;
			m_Running = false;
		}
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		AU_CORE_INFO("Creating window {0} ({1},{2})", props.Title, props.Width, props.Height);

		if (!WindowInitialised)
		{
			//TO DO
			//Initialising Window Code If Any:
		}

		wnd = Win32_Window::Create(m_Data.Width, m_Data.Height, m_Data.Title.c_str());


	}
	void WindowsWindow::Shutdown()
	{
		wnd->Destroy();
	}
}