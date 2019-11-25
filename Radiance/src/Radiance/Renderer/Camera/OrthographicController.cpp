#include "pch.h"
#include "OrthographicController.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)


namespace Radiance
{
	OrthographicController::OrthographicController(float _aspectRatio, float _zoomFactor)
		: m_Camera(-_aspectRatio * _zoomFactor, _aspectRatio * _zoomFactor, -_zoomFactor, _zoomFactor),
		m_AspectRatio(_aspectRatio),
		m_ZoomFactor(_zoomFactor),
		m_TranslationSpeed(1.0f),
		m_RotationSpeed(0.015f)
	{
	}

	void OrthographicController::Update(DataTime _time)
	{
		UpdateAttributes(_time);
	}

	void OrthographicController::SetCameraAttributes()
	{
		m_Camera.SetLeft(-m_AspectRatio * m_ZoomFactor);
		m_Camera.SetRight(+m_AspectRatio * m_ZoomFactor);
		m_Camera.SetBottom(-m_ZoomFactor);
		m_Camera.SetTop(+m_ZoomFactor);
	}

	void OrthographicController::UpdateAttributes(DataTime _time)
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

		glm::vec3 position = m_Camera.GetPosition();
		position += direction * _time.dt * m_TranslationSpeed;
		m_Camera.SetPosition(position);

		glm::vec2 mousePos = Input::GetMousePosition();
		if (Input::IsMouseButtonPressed(RAD_MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 deltaPos = mousePos - m_PrevMousePos;
			deltaPos *= m_RotationSpeed;

			glm::vec2 rot = m_Camera.GetRotation();
			rot.y += deltaPos.x;
			rot.x += deltaPos.y;
			m_Camera.SetRotation(rot);
		}
		m_PrevMousePos = mousePos;

	}

}