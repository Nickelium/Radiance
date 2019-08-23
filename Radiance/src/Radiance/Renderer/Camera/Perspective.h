#pragma once

#include "Camera.h"

namespace Radiance
{
	class Perspective : public Camera
	{
	public:
		Perspective(float _aspectRatio, float _fovV, float _near = 0.1f, float _far = 10000.0f);
	protected:
		void UpdateMatrices();

		float m_AspectRatio, m_FovV;
		float m_Near, m_Far;
	};
}
