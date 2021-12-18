#pragma once

#include "Aurora/Window.h"
#include "Win32_Window.h"


namespace Aurora {
	class D3D11Graphics;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		virtual void OnUpdate(bool &m_Running) override;

		virtual inline unsigned int GetWidth() const override { return m_Data.Width; };
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; };

		virtual inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void SetViewPort(unsigned int width,unsigned int height) override;
		virtual void makeGraphics() override;
		virtual Graphics* Gfx() override;

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

			EventCallbackFn EventCallback;
		};

		WindowsData m_Data;
		Graphics* pGfx;

		Win32_Window* m_Window;
	};

	
}
