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

	void Mesh::SetNormals(std::vector<glm::vec3> _normals)
	{
		m_Normals = _normals;
	}

	void Mesh::SetIndices(std::vector<uint32_t> _indices)
	{
		m_Indices = _indices;
	}

}