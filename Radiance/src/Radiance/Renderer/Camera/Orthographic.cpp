#include "pch.h"
#include "Orthographic.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)

namespace Radiance
{
	Orthographic::Orthographic(
		float _left, float _right,
		float _bottom, float _top,
		float _near /*= 1*/, float _far /*= 100*/)
		: m_LeftSide(_left), m_RightSide(_right),
		m_BottomSide(_bottom), m_TopSide(_top),
		m_Near(_near), m_Far(_far)
	{
		RebuildMatrices();
	}

	void Orthographic::RebuildMatrices()
	{
		UpdateView();
		UpdateProjection();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Orthographic::UpdateView()
	{
		//NOTE: to map with [theta,phi] = [0,0] to front vector
		float thetaRad = glm::radians(m_Rotation.x - 90.0f);
		float phiRad = glm::radians(m_Rotation.y + 90.0f);

		m_Forward.x = sin(thetaRad) * cos(phiRad);
		m_Forward.y = cos(thetaRad);
		m_Forward.z = sin(thetaRad) * sin(phiRad);

		m_Right = glm::normalize(glm::cross(m_Forward, m_Up));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	void Orthographic::UpdateProjection()
	{
		m_ProjectionMatrix = glm::ortho(m_LeftSide, m_RightSide, m_BottomSide, m_TopSide, m_Near, m_Far);
	}
}