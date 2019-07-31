#pragma once

#include "Camera.h"

namespace Radiance
{
	class Perspective : public Camera
	{
	public:
		Perspective(float _aspectRatio, float _fovV, float _near = 0.001f, float _far = 100.0f);
		void SetAspectRatio(float _aspectRatio);
		void SetFovV(float _fovV);
	protected:
		void UpdateMatrices();

		void UpdateCombined();
		void UpdateView();
		void UpdateProjection();

		float m_AspectRatio, m_FovV;
		float m_Near, m_Far;
	};
}
