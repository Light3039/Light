#include "ltpch.h"
#include "glGraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Light {

	glGraphicsContext::glGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		m_GraphicsAPI = GraphicsAPI::OpenGL;

		glfwMakeContextCurrent(windowHandle);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		LT_ENGINE_INFO("glGraphicsContext:");
		LT_ENGINE_INFO("        Renderer: {}", glGetString(GL_RENDERER));
		LT_ENGINE_INFO("        Version: {}", glGetString(GL_VERSION));
	}

}