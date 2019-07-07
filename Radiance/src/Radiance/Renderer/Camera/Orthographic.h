#pragma once

#include "Camera.h"

namespace Radiance
{
	class Orthographic : public Camera
	{
	public:
		Orthographic(float _left, float _right, float _bottom, float _top, float _near = 1, float _far = 100);

		inline virtual const glm::vec3& GetPosition() const override { return m_Position; }
		inline virtual const glm::vec3& GetRotations() const override { return m_Rotations; }
		inline virtual float GetRotationX() const override { return m_Rotations.x; }
		inline virtual float GetRotationY() const override { return m_Rotations.y; }
		inline virtual float GetRotationZ() const override { return m_Rotations.z; }

		inline virtual void SetPosition(glm::vec3 _position) override
		{	m_Position = _position; UpdateMatrices(); }
		inline virtual void SetRotations(const glm::vec3& _rotations) override 
		{ m_Rotations = _rotations; UpdateMatrices(); }
		inline virtual void SetRotationX(float _rotationX) override
		{ m_Rotations.x = _rotationX; UpdateMatrices(); }
		inline virtual void SetRotationY(float _rotationY) override
		{ m_Rotations.y = _rotationY; UpdateMatrices(); }
		inline virtual void SetRotationZ(float _rotationZ) override
		{ m_Rotations.z = _rotationZ; UpdateMatrices(); }


		inline virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
		inline virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		inline virtual const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }

	private:
		void UpdateMatrices();

		float m_Left, m_Right;
		float m_Bottom, m_Top;
		float m_Near, m_Far;

		glm::mat4 m_ViewProjectionMatrix; //VP for caching
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotations;
	};
}