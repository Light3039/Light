#pragma once

#include "Base.h"

#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

#include <string>

namespace Light {

	class Layer
	{
	private:
		std::string m_Name;

	public:
		Layer(const std::string& name): m_Name(name) {}
		virtual ~Layer() = default;

		inline const std::string& GetName() const { return m_Name; }

		// Updates
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnUserInterfaceUpdate() {}

		// Mouse events
		virtual bool OnMouseMoved(const MouseMovedEvent& event) { return false; }
		virtual bool OnButtonPressed(const ButtonPressedEvent& event) { return false; }
		virtual bool OnButtonReleased(const ButtonReleasedEvent& event) { return false; }
		virtual bool OnWheelScrolled(const WheelScrolledEvent& event) { return false; }

		// Keyboard events
		virtual bool OnKeyPressed(const KeyPressedEvent& event) { return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& event) { return false; }

		// Window Events
		virtual bool OnWindowClosed(const WindowClosedEvent& event) { return false; }
		virtual bool OnWindowResized(const WindowResizedEvent& event) { return false; }
		virtual bool OnWindowMoved(const WindowMovedEvent& event) { return false; }
		virtual bool OnWindowLostFocus(const WindowLostFocusEvent& event) { return false; }
		virtual bool OnWindowGainFocus(const WindowGainFocusEvent& event) { return false; }
	};

	class TestLayer : public Layer
	{
	public:
		TestLayer(const std::string& name): Layer(name) {}

		// Mouse events
		virtual bool OnMouseMoved(const MouseMovedEvent& event) override { LT_ENGINE_TRACE("{}", event.GetInfoLog()); return false; }
		virtual bool OnButtonPressed(const ButtonPressedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnButtonReleased(const ButtonReleasedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnWheelScrolled(const WheelScrolledEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }

		// Keyboard events
		virtual bool OnKeyPressed(const KeyPressedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }

		// Window events
		virtual bool OnWindowClosed(const WindowClosedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnWindowResized(const WindowResizedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnWindowMoved(const WindowMovedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnWindowLostFocus(const WindowLostFocusEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnWindowGainFocus(const WindowGainFocusEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	};

}