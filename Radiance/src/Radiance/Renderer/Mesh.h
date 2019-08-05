#pragma once

namespace Radiance
{
	class Mesh
	{
	public:
		Mesh();
		void SetPositions(std::vector<glm::vec3> _positions);
		void SetNormals(std::vector<glm::vec3> _normals);
		void SetTexCoords(std::vector<glm::vec2> _texCoords);
		void SetIndices(std::vector<uint32_t> _indices);

		inline const std::vector<glm::vec3>& GetPositions() const { return m_Positions; }
		inline const std::vector<glm::vec3>& GetNormals() const { return m_Normals; }
		inline const std::vector<glm::vec2>& GetTexCoords() const { return m_TexCoords; }
		inline const std::vector<uint32_t>& GetIndices() const { return m_Indices; }

		inline bool HasPositions() const { return m_Positions.size() > 0; }
		inline bool HasNormals() const { return m_Normals.size() > 0; }
		inline bool HasTexCoords() const { return m_TexCoords.size() > 0; }
		inline bool HasIndices() const { return m_Indices.size() > 0; }

		inline int GetNbVertices() const { return static_cast<int>(m_Positions.size()); }
		inline int GetNbIndices() const { return static_cast<int>(m_Indices.size()); }

	private:
		//ORDER CONVENTION
		//POS
		//NORMAL
		//TEXC

		//REQUIRE
		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec3> m_Normals;
		
		std::vector<glm::vec2> m_TexCoords;

		std::vector<uint32_t> m_Indices;
	};
}
