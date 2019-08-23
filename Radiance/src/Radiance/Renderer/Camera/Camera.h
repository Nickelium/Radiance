#pragma once

#include <glm/glm.hpp>

namespace Radiance
{
	class Camera
	{
	public:
		Camera() : position(0, 0, 0), m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::mat4(1.0)), m_ViewProjectionMatrix(glm::mat4(1.0)) {}
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		virtual void Update(DataTime _time) = 0;

		glm::vec3 position = {0, 0, 0};

		//theta & phi
		glm::vec2 rot = {0.0f, 0.0f};
	protected:
		glm::vec3 m_Forward = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Right = { 1.0f, 0.0f, 0.0f };
		glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };

		glm::mat4 m_ViewProjectionMatrix; //VP for caching
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};
}
