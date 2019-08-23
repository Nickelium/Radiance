#include "pch.h"
#include "MeshRender.h"

#include "API/VertexArray.h"
#include "Material.h"
#include "Mesh.h"

#include "API/RenderDevice.h"

namespace Radiance
{
	
	MeshRender::MeshRender(Mesh* _mesh, Material* _material)
		: m_Mesh(_mesh), m_Material(_material)
	{
		BuildVertexArray();
	}

	MeshRender::~MeshRender()
	{
		delete m_VertexArray;
		delete m_Mesh;
		delete m_Material;
	}

	void MeshRender::Bind()
	{
		m_VertexArray->Bind();
		m_Material->Bind();
	}

	void MeshRender::UnBind()
	{
		m_VertexArray->UnBind();
		m_Material->UnBind();
	}

	void MeshRender::BuildVertexArray()
	{
		std::vector<float> vertices;

		const std::vector<glm::vec3>& positions = m_Mesh->GetPositions();
		const std::vector<glm::vec3>& normals = m_Mesh->GetNormals();

		const std::vector<glm::vec2>& texCoords = m_Mesh->GetTexCoords();

		const std::vector<uint32_t>& indices = m_Mesh->GetIndices();

		if(!m_Mesh->HasPositions())
			RAD_CORE_INFO("Mesh doesn't contain Positions");
		if (!m_Mesh->HasNormals())
			RAD_CORE_INFO("Mesh doesn't contain Normals");
		if (!m_Mesh->HasTexCoords())
			RAD_CORE_INFO("Mesh doesn't contain TexCoords");
		if (!m_Mesh->HasIndices())
			RAD_CORE_INFO("Mesh doesn't contain Indices");


		int nbVertices = m_Mesh->GetNbVertices();
		for (int i = 0; i < nbVertices; ++i)
		{
			if (m_Mesh->HasPositions())
			{
				vertices.push_back(positions[i].x);
				vertices.push_back(positions[i].y);
				vertices.push_back(positions[i].z);
			}

			if (m_Mesh->HasNormals())
			{
				vertices.push_back(normals[i].x);
				vertices.push_back(normals[i].y);
				vertices.push_back(normals[i].z);
			}

			if (m_Mesh->HasTexCoords())
			{
				vertices.push_back(texCoords[i].x);
				vertices.push_back(texCoords[i].y);
			}

		}

		auto rd = Locator::Get<RenderDevice>();
		VertexArray* vertexArray = rd->CreateVertexArray();
		VertexBuffer* vertexBuffer = rd->CreateVertexBuffer(vertices);
		BufferLayout layout;

		if (m_Mesh->HasPositions())
			layout.AddElement({ DataType::Float3, "a_Position" });
		if (m_Mesh->HasNormals())
			layout.AddElement({ DataType::Float3, "a_Normal" });
		if (m_Mesh->HasTexCoords())
			layout.AddElement({ DataType::Float2, "a_TexCoord" });
		
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		if (m_Mesh->HasIndices())
		{
			IndexBuffer* indexBuffer = rd->CreateIndexBuffer(indices);
			vertexArray->SetIndexBuffer(indexBuffer);
		}
		else RAD_CORE_WARN("Mesh doesn't contain Indices");

		m_VertexArray = vertexArray;
	}

}