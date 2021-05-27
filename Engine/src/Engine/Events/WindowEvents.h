#pragma once

#include "Base.h"

#include "Event.h"

#include <glm/glm.hpp>

#include <sstream>

namespace Light {

	class WindowClosedEvent : public Event
	{
	public:
		virtual std::string GetInfoLog() const override
		{
			return "WindowClosedEvent";
		}
		EVENT_TYPE(WindowClosed)
		EVENT_CATEGORY(WindowEventCategory)
	};

	class WindowMovedEvent : public Event 
	{
	private:
		const glm::ivec2 m_Position;

	public:
		WindowMovedEvent(int x, int y): m_Position(x, y) {}

		const glm::ivec2& GetPosition() { return m_Position; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "WindwoMoved: " << m_Position.x << ", " << m_Position.y;
			return ss.str();
;		}
		EVENT_TYPE(WindowMoved)
		EVENT_CATEGORY(WindowEventCategory)
	};

	class WindowResizedEvent : public Event
	{
	private:
		const glm::ivec2 m_Size;

	public:
		WindowResizedEvent(int width, int height): m_Size(width, height) {}

		const glm::ivec2& GetSize() { return m_Size; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "WindowResized: " << m_Size.x << ", " << m_Size.y;
			return ss.str();
		}
		EVENT_TYPE(WindowResized)
		EVENT_CATEGORY(WindowEventCategory)
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		virtual std::string GetInfoLog() const override
		{
			return "WindowLostFocus";
		}
		EVENT_TYPE(WindowLostFocus)
		EVENT_CATEGORY(WindowEventCategory)
	};

	class WindowGainFocusEvent : public Event
	{
	public:
		virtual std::string GetInfoLog() const override
		{
			return "WindowGainFocus";
		}
		EVENT_TYPE(WindowGainFocus)
		EVENT_CATEGORY(WindowEventCategory)
	};

}