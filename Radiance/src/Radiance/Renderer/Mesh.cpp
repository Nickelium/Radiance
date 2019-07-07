#include "pch.h"
#include "Mesh.h"

#include "API/VertexArray.h"
#include "API/Shader.h"

namespace Radiance
{
	
	Mesh::Mesh(VertexArray* _vertexArray, Shader* _shader)
		: m_VertexArray(_vertexArray), m_Shader(_shader)
	{
	}

	Mesh::~Mesh()
	{
		delete m_VertexArray;
		delete m_Shader;
	}

	void Mesh::Bind()
	{
		m_VertexArray->Bind();
		m_Shader->Bind();
	}

	void Mesh::UnBind()
	{
		m_VertexArray->UnBind();
		m_Shader->UnBind();
	}

}