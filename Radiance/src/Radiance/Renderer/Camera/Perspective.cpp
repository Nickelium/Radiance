#include "pch.h"
#include "Perspective.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)

namespace Radiance
{
	Perspective::Perspective(
		float _aspectRatio, float _fovV,
		float _near /*= 1*/, float _far /*= 100*/)
		: m_AspectRatio(_aspectRatio), m_FovV(_fovV),
		m_Near(_near), m_Far(_far)
	{
		UpdateMatrices();
	}

	void Perspective::SetAspectRatio(float _aspectRatio)
	{
		m_AspectRatio = _aspectRatio;
		UpdateProjection();
	}

	void Perspective::SetFovV(float _fovV)
	{
		m_FovV = _fovV;
		UpdateProjection();
	}

	void Perspective::UpdateMatrices()
	{
		UpdateView();
		UpdateProjection();
	}

	void Perspective::UpdateCombined()
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Perspective::UpdateView()
	{
		glm::mat4 R = glm::eulerAngleXYZ(
			glm::radians(rotation.x),
			glm::radians(rotation.y),
			glm::radians(rotation.z));
		glm::vec3 forward = R * glm::vec4(0, 0, -1, 0);
		glm::vec3 up = R * glm::vec4(0, 1, 0, 0);
		m_ViewMatrix = glm::lookAt(position, position + forward, up);

		UpdateCombined();
	}

	void Perspective::UpdateProjection()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FovV), m_AspectRatio, m_Near, m_Far);

		UpdateCombined();
	}

}