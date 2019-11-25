#pragma once

#include <glm/glm.hpp>

namespace Radiance
{
	class Camera
	{
	public:
		Camera(const glm::vec3& _position = {}, const glm::vec2& _rotation = {}) :
			m_Position(_position), m_Rotation(_rotation), 
			m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::mat4(1.0)), 
			m_ViewProjectionMatrix(glm::mat4(1.0)) {}
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		inline void SetPosition(const glm::vec3& _position) { m_Position = _position; RebuildMatrices(); }
		inline void SetRotation(const glm::vec2& _rotation) { m_Rotation = _rotation; RebuildMatrices(); }

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec2 GetRotation() const { return m_Rotation; }

		//theta & phi
	protected:
		virtual void RebuildMatrices() = 0;

		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		glm::vec2 m_Rotation = {0.0f, 0.0f};

		glm::mat4 m_ViewProjectionMatrix; //VP for caching
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};
}
