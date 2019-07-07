#pragma once

namespace Radiance
{
	class VertexArray;
	class Shader;
	class Mesh
	{
	public:
		Mesh(VertexArray* _vertexArray, Shader* _shader);
		~Mesh();

		void Bind();
		void UnBind();

		inline VertexArray* GetVertexArray() const { return m_VertexArray; }
		inline Shader* GetShader() const { return m_Shader; }

	private:
		VertexArray* m_VertexArray;
		Shader* m_Shader;
	};
}
