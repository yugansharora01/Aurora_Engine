#include "pch.h"
#include "WindowsWindow.h"
#include "Aurora/Renderer/FrameBuffer.h"
#include "Platform/DirectX/D3D11Graphics.h"

namespace Aurora {

	static bool WindowInitialised = false;

	std::shared_ptr<Window> Window::Create(const WindowProps& props)
	{
		return std::make_shared<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
		makeGraphics();
	}

	WindowsWindow::~WindowsWindow()
	{
		Close();
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

	void WindowsWindow::SetWindowData( unsigned int Width, unsigned int Height, std::string Title)
	{
		if(Title != "")
			m_Data.Title = Title;
		m_Data.Width = Width;
		m_Data.Height = Height;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::SetViewPort(unsigned int width, unsigned int height)
	{
		pGfx->SetViewPort(width, height);
	}

	void WindowsWindow::makeGraphics()
	{
		auto hwnd = (void *)m_Window->GetHandle();
		pGfx = Graphics::Create(hwnd);
	}

	Ref<Graphics> WindowsWindow::Gfx()
	{
		return pGfx;
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

		m_Window = Win32_Window::Create(m_Data.Width, m_Data.Height, m_Data.Title.c_str());
	}
	void WindowsWindow::Close()
	{
		m_Window->Destroy();
	}
}