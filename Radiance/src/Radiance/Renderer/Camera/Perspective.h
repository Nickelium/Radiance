#pragma once

#include "Camera.h"

namespace Radiance
{
	class Perspective : public Camera
	{
	public:
		Perspective(float _aspectRatio, float _fovV, float _near = 0.1f, float _far = 10000.0f);

		inline float GetAspectRatio() const { return m_AspectRatio; }
		inline float GetFovV() const { return m_FovV; }
		inline float GetNear() const { return m_Near; }
		inline float GetFar() const { return m_Far; }

		inline void SetAspectRatio(float _aspectRatio) { m_AspectRatio = _aspectRatio; }
		inline void SetFovV(float _fovV) { m_FovV = _fovV; }
		inline void SetNear(float _near) { m_Near = _near; }
		inline void SetFar(float _far) { m_Far = _far; }


		inline glm::vec3 GetForward() const { return m_Forward; }
		inline glm::vec3 GetRight() const { return m_Right; }
		inline glm::vec3 GetUp() const { return m_Up; }

		inline void SetForward(const glm::vec3 _forward) { m_Forward = _forward; }
		inline void SetRight(const glm::vec3 _right) { m_Right = _right; }
		inline void SetUp(const glm::vec3 _up) { m_Up = _up; }

	private:
		virtual void RebuildMatrices();

		void UpdateView();
		void UpdateProjection();

		glm::vec3 m_Forward = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Right = { 1.0f, 0.0f, 0.0f };
		glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };

		float m_AspectRatio, m_FovV;
		float m_Near, m_Far;
	};
}
