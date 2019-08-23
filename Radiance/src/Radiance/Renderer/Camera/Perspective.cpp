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
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FovV), m_AspectRatio, m_Near, m_Far);
		UpdateMatrices();
	}

	void Perspective::UpdateMatrices()
	{
		//NOTE: to map with [theta,phi] = [0,0] to front vector
		float thetaRad = glm::radians(rot.x - 90.0f);
		float phiRad = glm::radians(rot.y + 90.0f);

		m_Forward.x = sin(thetaRad) * cos(phiRad);
		m_Forward.y = cos(thetaRad);
		m_Forward.z = sin(thetaRad) * sin(phiRad);

		m_Right = glm::normalize(glm::cross(m_Forward, m_Up));

		m_ViewMatrix = glm::lookAt(position, position + m_Forward, m_Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}