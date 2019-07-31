#pragma once

#include "Camera.h"

namespace Radiance
{
	class Perspective : public Camera
	{
	public:
		Perspective(float _aspectRatio, float _fovV, float _near = 0.001f, float _far = 100.0f);
	protected:
		void UpdateMatrices();

		float m_AspectRatio, m_FovV;
		float m_Near, m_Far;
	};
}
