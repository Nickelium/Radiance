#pragma once

#include <glm/glm.hpp>

namespace Radiance
{
	class Camera
	{
	public:
		virtual const glm::vec3& GetPosition() const = 0;
		virtual const glm::vec3& GetRotations() const = 0;
		virtual float GetRotationX() const = 0;
		virtual float GetRotationY() const = 0;
		virtual float GetRotationZ() const = 0;

		virtual void SetPosition(glm::vec3 _position) = 0;
		virtual void SetRotations(const glm::vec3& _rotations) = 0;
		virtual void SetRotationX(float _rotationX) = 0;
		virtual void SetRotationY(float _rotationY) = 0;
		virtual void SetRotationZ(float _rotationZ) = 0;

		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
	};
}
