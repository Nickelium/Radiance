#pragma once

#include "Camera.h"

namespace Radiance
{
	class Orthographic : public Camera
	{
	public:
		Orthographic(float _left, float _right, float _bottom, float _top, float _near = 1, float _far = 10000);
	protected:
		void UpdateMatrices();

		float m_LeftSide, m_RightSide;
		float m_BottomSide, m_TopSide;
		float m_Near, m_Far;
	};
}