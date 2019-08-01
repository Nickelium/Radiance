#pragma once

namespace Radiance
{
	class VertexArray;
	class Mesh;
	class Material;

	class MeshRender
	{
	public:
		MeshRender(Mesh* _mesh, Material* _material);
		~MeshRender();

		void Bind();
		void UnBind();

		inline VertexArray* GetVertexArray() const { return m_VertexArray; }
		inline Mesh* GetMesh() const { return m_Mesh; }
		inline Material* GetMaterial() const { return m_Material; }

	private:
		void BuildVertexArray();

		VertexArray* m_VertexArray;

		Mesh* m_Mesh;
		Material* m_Material;
	};
}
