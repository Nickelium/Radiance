#pragma once

#include "Camera.h"

namespace Radiance
{
	class Orthographic : public Camera
	{
	public:
		Orthographic(float _left, float _right, 
			float _bottom, float _top,
			float _near = 1, float _far = 10000);

		inline float GetLeftSide() const { return m_LeftSide; }
		inline float GetRightSide() const { return m_RightSide; }
		inline float GetBottomSide() const { return m_BottomSide; }
		inline float GetTopSide() const { return m_TopSide; }
		inline float GetNear() const { return m_Near; }
		inline float GetFar() const { return m_Far; }

		inline void SetLeft(float _left) { m_LeftSide = _left; }
		inline void SetRight(float _right) { m_RightSide = _right; }
		inline void SetBottom(float _bottom) { m_BottomSide = _bottom; }
		inline void SetTop(float _top) { m_TopSide = _top; }
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

		float m_LeftSide, m_RightSide;
		float m_BottomSide, m_TopSide;
		float m_Near, m_Far;
	};
}