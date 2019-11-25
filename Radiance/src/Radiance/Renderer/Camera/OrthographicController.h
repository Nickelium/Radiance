#pragma once

#include "Orthographic.h"

namespace Radiance
{
	class OrthographicController
	{
	public:
		OrthographicController(float _aspectRatio = 16.0f / 9.0f, float _zoomFactor = 1.0f);
		
		void Update(DataTime _time);

		inline void SetAspectRatio(float _aspectRatio) { m_AspectRatio = _aspectRatio; SetCameraAttributes(); }
		inline void SetZoomFactor(float _zoomFactor) { m_ZoomFactor = _zoomFactor; }
		inline float GetAspectRatio() const { return m_AspectRatio; }
		inline float GetZoomFactor() const { return m_ZoomFactor; }

		inline void SetPosition(const glm::vec3& _position) { m_Camera.SetPosition(_position); }
		inline void SetRotation(const glm::vec2& _rotation) { m_Camera.SetRotation(_rotation); }
		inline glm::vec3 GetPosition() const { return m_Camera.GetPosition(); }
		inline glm::vec2 GetRotation() const { return m_Camera.GetRotation(); }

		inline float GetNear() const { return m_Camera.GetNear(); }
		inline float GetFar() const { return m_Camera.GetFar(); }
		inline void SetNear(float _near) { m_Camera.SetNear(_near); }
		inline void SetFar(float _far) { m_Camera.SetFar(_far); }

		const Camera& GetCamera() const { return m_Camera; }

	private:
		void SetCameraAttributes();

		void UpdateAttributes(DataTime _time);

		float m_AspectRatio;
		float m_ZoomFactor;

		float m_TranslationSpeed;
		float m_RotationSpeed;

		glm::vec2 m_PrevMousePos;

		Orthographic m_Camera;
	};
}