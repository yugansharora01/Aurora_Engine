#pragma once

#include "pch.h"

#include "Aurora/Core.h"
#include "Aurora/Events/Events.h"
#include "Aurora/Log.h"

namespace Aurora {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Aurora Engine", unsigned int width = 1200, unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	class AURORA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {};
		virtual void OnUpdate(bool &m_Running) = 0;

		virtual inline unsigned int GetWidth() const = 0;
		virtual inline unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	};

}