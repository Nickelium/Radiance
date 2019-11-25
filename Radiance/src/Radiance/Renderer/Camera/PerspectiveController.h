#pragma once

#include "Perspective.h"

namespace Radiance
{
	class PerspectiveController
	{
	public:
		PerspectiveController(float _aspectRatio = 16.0f / 9.0f, float _fovV = 60.0f);
		void Update(DataTime _time);

		inline void SetSpeed(float _speed) { m_MovementSpeed = _speed; }
		inline void SetSensitivity(float _sensitivity) { m_MouseSensitivity = _sensitivity; }
		inline float GetSpeed() const { return m_MovementSpeed; }
		inline float GetSensitivity() const { return m_MouseSensitivity; }

		inline void SetPosition(const glm::vec3& _position) { m_Camera.SetPosition(_position); }
		inline void SetRotation(const glm::vec2& _rotation) { m_Camera.SetRotation(_rotation); }

		inline glm::vec3 GetPosition() const { return m_Camera.GetPosition(); }
		inline glm::vec2 GetRotation() const { return m_Camera.GetRotation(); }

		inline float GetAspectRatio() const { return m_Camera.GetAspectRatio(); }
		inline float GetFovV() const { return m_Camera.GetFovV(); }
		inline float GetNear() const { return m_Camera.GetNear(); }
		inline float GetFar() const { return m_Camera.GetFar(); }

		inline void SetAspectRatio(float _aspectRatio) { m_Camera.SetAspectRatio(_aspectRatio); }
		inline void SetFovV(float _fovV) { m_Camera.SetFovV(_fovV); }
		inline void SetNear(float _near) { m_Camera.SetNear(_near); }
		inline void SetFar(float _far) { m_Camera.SetFar(_far); }

		const Camera& GetCamera() const { return m_Camera; }
	private:
		void UpdateAttributes(DataTime _time);

		float m_MovementSpeed;
		float m_MouseSensitivity;
		
		glm::vec2 m_PrevMousePos;

		Perspective m_Camera;
	};
}