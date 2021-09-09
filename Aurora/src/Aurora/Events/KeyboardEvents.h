#pragma once

#include "Events.h"

namespace Aurora
{
	class AURORA_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int Keycode)
			:m_KeyCode(Keycode){}

		int m_KeyCode;
	};

	class AURORA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode,int repeatCount)
			:KeyEvent(keycode),m_RepeatCount(repeatCount){}
		
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeypressedEvent" << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class AURORA_API KeyReleasededEvent : public KeyEvent
	{
	public:
		KeyReleasededEvent(int keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasededEvent" << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};

	class AURORA_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent" << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};
}