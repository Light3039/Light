#pragma once

#include "Base.h"
#include "Core/Window.h"

struct GLFWwindow;

namespace Light {

	class Event;
	class WindowResizedEvent;

	class wWindow : public Window
	{
	private:
		GLFWwindow* m_Handle = nullptr;

		std::function<void(Event&)> m_EventCallback;

	public: 
		wWindow(std::function<void(Event&)> callback);

		~wWindow();

		void PollEvents() override;
		void OnEvent(const Event& event) override;

		//** SETTERS **//
		void SetProperties(const WindowProperties& properties, bool affectVisibility = false) override;

		void SetTitle(const std::string& title) override;

		void SetSize(const glm::uvec2& size, bool additive = false) override;

		void SetVSync(bool vsync, bool toggle = false) override;
		void SetVisibility(bool visible, bool toggle = false) override;

	private:
		void BindGlfwEvents();

		void OnWindowResize(const WindowResizedEvent& event);
	};

}