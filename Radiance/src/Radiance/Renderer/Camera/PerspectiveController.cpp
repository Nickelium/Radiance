#include "pch.h"
#include "PerspectiveController.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)

namespace Radiance
{
	PerspectiveController::PerspectiveController(float _aspectRatio, float _fovV)
		: m_Camera(_aspectRatio, _fovV), 
		m_MovementSpeed(150.0f),
		m_MouseSensitivity(0.15f)
	{
	}

	void PerspectiveController::Update(DataTime _time)
	{
		UpdateAttributes(_time);
	}

	void PerspectiveController::UpdateAttributes(DataTime _time)
	{
		glm::vec3 direction(0, 0, 0);
		if (Input::IsKeyPressed(RAD_KEY_A))
			direction += -m_Camera.GetRight();
		else if (Input::IsKeyPressed(RAD_KEY_D))
			direction += m_Camera.GetRight();
		if (Input::IsKeyPressed(RAD_KEY_W))
			direction += m_Camera.GetForward();
		else if (Input::IsKeyPressed(RAD_KEY_S))
			direction += -m_Camera.GetForward();
		if (Input::IsKeyPressed(RAD_KEY_SPACE))
			direction += m_Camera.GetUp();
		else if (Input::IsKeyPressed(RAD_KEY_LEFT_ALT))
			direction += -m_Camera.GetUp();

		if (glm::length(direction) > 1e-3f)
			direction = glm::normalize(direction);
	
		glm::vec3 position = m_Camera.GetPosition() + direction * _time.dt * m_MovementSpeed;
		m_Camera.SetPosition(position);

		glm::vec2 mousePos = Input::GetMousePosition();
		if (Input::IsMouseButtonPressed(RAD_MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 deltaPos = mousePos - m_PrevMousePos;
			deltaPos *= m_MouseSensitivity;

			glm::vec2 rot = m_Camera.GetRotation();
			rot.y += deltaPos.x;
			rot.x += deltaPos.y;
			m_Camera.SetRotation(rot);
		}
		m_PrevMousePos = mousePos;

	}

}