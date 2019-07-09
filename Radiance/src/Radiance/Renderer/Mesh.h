#pragma once

namespace Radiance
{
	class Mesh
	{
	public:
		Mesh();
		void SetPositions(std::vector<glm::vec3> _positions);
		void SetIndices(std::vector<uint32_t> _indices);

		const std::vector<glm::vec3>& GetPositions();
		const std::vector<uint32_t>& GetIndices();

		inline int GetNbVertices() const { return static_cast<int>(m_Positions.size()); }
		inline int GetNbIndices() const { return static_cast<int>(m_Indices.size()); }

	private:
		std::vector<glm::vec3> m_Positions;
		std::vector<uint32_t> m_Indices;

	};
}
