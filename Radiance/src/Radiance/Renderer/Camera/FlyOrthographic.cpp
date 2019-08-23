#include "pch.h"
#include "FlyOrthographic.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)


namespace Radiance
{
	FlyOrthographic::FlyOrthographic(float _speed, float _sensitivity)
		: Orthographic(-160.0f, 160.0f, -90.0f, 90.0f),
		m_MouseSpeed(_speed),
		m_MouseSensitivity(_sensitivity)
	{
	}

	void FlyOrthographic::Update(DataTime _time)
	{
		UpdateAttributes(_time);
		UpdateMatrices();
	}

	void FlyOrthographic::UpdateAttributes(DataTime _time)
	{
		glm::vec3 direction(0, 0, 0);
		if (Input::IsKeyPressed(RAD_KEY_A))
			direction += -m_Right;
		else if (Input::IsKeyPressed(RAD_KEY_D))
			direction += m_Right;
		if (Input::IsKeyPressed(RAD_KEY_W))
			direction += m_Forward;
		else if (Input::IsKeyPressed(RAD_KEY_S))
			direction += -m_Forward;
		if (Input::IsKeyPressed(RAD_KEY_SPACE))
			direction += m_Up;
		else if (Input::IsKeyPressed(RAD_KEY_LEFT_ALT))
			direction += -m_Up;

		if (glm::length(direction) > 1e-3f)
			direction = glm::normalize(direction);

		position += direction * _time.dt * m_MouseSpeed;

		glm::vec2 mousePos = Input::GetMousePosition();
		if (Input::IsMouseButtonPressed(RAD_MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 deltaPos = mousePos - m_PrevMousePos;
			deltaPos *= m_MouseSensitivity;

			rot.y += deltaPos.x;
			rot.x += deltaPos.y;
		}
		m_PrevMousePos = mousePos;

	}

}