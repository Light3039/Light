#include "ltpch.h"
#include "Camera.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {
	
	Camera::Camera(const glm::vec2& position, float aspectRatio, float zoomLevel)
		: m_Up(0.0f, 1.0f, 0.0f), m_Position(position), m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel)
	{
	}

	void Camera::CalculateView()
	{
		m_View = glm::lookAt(glm::vec3(m_Position, 100.0f), glm::vec3(m_Position, 0.0f), m_Up);
	}

	void Camera::CalculateProjection()
	{
		m_Projection = glm::ortho(-m_ZoomLevel * m_AspectRatio,
		                          +m_ZoomLevel * m_AspectRatio,
		                          -m_ZoomLevel,
		                          +m_ZoomLevel,
		                           FLT_MAX, FLT_MIN);
	}

	void Camera::Move(const glm::vec2& position)
	{
		m_Position += position;
	}

}