#pragma once

#include "pch.h"

#include "Aurora/Events/Events.h"
#include "Aurora/Core/Log.h"

namespace Aurora {
	class Graphics;

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Aurora Engine", unsigned int width = 800, unsigned int height = 600)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	class AURORA_API Window
	{
	public:
		virtual ~Window() {};
		virtual void OnUpdate(bool &m_Running) = 0;
		virtual void Close() = 0;

		virtual inline std::pair<unsigned int, unsigned int> GetPos() = 0;
		virtual inline std::pair<unsigned int, unsigned int> GetClientPos() = 0;
		virtual inline unsigned int GetWidth() const = 0;
		virtual inline unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetWindowData(unsigned int width, unsigned int height, std::string Title = "") = 0;

		virtual void makeGraphics() = 0;
		virtual Ref<Graphics> Gfx() = 0;

		static std::shared_ptr<Window> Create(const WindowProps& props = WindowProps());
	
	};

}