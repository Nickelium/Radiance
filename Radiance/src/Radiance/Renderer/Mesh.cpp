#include "pch.h"
#include "Mesh.h"

namespace Radiance
{
	Mesh::Mesh()
	{

	}

	void Mesh::SetPositions(std::vector<glm::vec3> _positions)
	{
		m_Positions = _positions;
	}

	void Mesh::SetIndices(std::vector<uint32_t> _indices)
	{
		m_Indices = _indices;
	}

	const std::vector<glm::vec3>& Mesh::GetPositions()
	{
		return m_Positions;
	}

	const std::vector<glm::uint32_t>& Mesh::GetIndices()
	{
		return m_Indices;
	}

}