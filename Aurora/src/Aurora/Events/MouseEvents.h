#pragma once

#include "Events.h"

#include <sstream>

namespace Aurora
{

	class AURORA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x,const float y)
			:m_MouseX(x),m_MouseY(y){}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse|EventCategoryInput)

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class AURORA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffSet,const float yOffSet)
			:m_Xoffset(xOffSet), m_Yoffset(yOffSet) {}

		inline float GetX() const { return m_Xoffset; }
		inline float GetY() const { return m_Yoffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_Xoffset << "," << m_Yoffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_Xoffset;
		float m_Yoffset;
	};

	class AURORA_API MouseButtonEvent : public Event
	{
	public:
		int GetMouseEvent() const { return m_Button; }
		
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(const int button)
			:m_Button(button){}
		float m_Button;
	};

	class AURORA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int button)
			:MouseButtonEvent(button) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)

	};

	class AURORA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int button)
			:MouseButtonEvent(button) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)

	};

}