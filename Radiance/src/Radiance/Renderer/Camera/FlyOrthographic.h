#pragma once

#include "Orthographic.h"

namespace Radiance
{
	class FlyOrthographic : public Orthographic
	{
	public:
		FlyOrthographic(float _speed = 150.0f, float _sensitivity = 0.15f);
		virtual void Update(DataTime _time) override;

	private:
		void UpdateAttributes(DataTime _time);

		float m_MouseSpeed;
		float m_MouseSensitivity;

		glm::vec2 m_PrevMousePos;

	};
}