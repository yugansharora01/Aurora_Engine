#pragma once

#include "Aurora/Core/Window.h"
#include "Win32_Window.h"


namespace Aurora {
	class D3D11Graphics;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		virtual void OnUpdate(bool &m_Running) override;

		virtual inline std::pair<unsigned int, unsigned int> GetPos() override { return m_Window->GetWindowPos(); }
		virtual inline std::pair<unsigned int, unsigned int> GetClientPos() override { return m_Window->GetClientPos();};
		virtual inline unsigned int GetWidth() const override { return m_Data.Width; };
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; };
		virtual void SetWindowData( unsigned int Width, unsigned int Height, std::string Title = "") override;

		
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void makeGraphics() override;
		virtual Ref<Graphics> Gfx() override;

		Win32_Window* GetWin32WindowPtr() { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Close();
	private:
		struct WindowsData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowsData m_Data;
		Ref<Graphics> pGfx;

		Win32_Window* m_Window;
	};

	
}
