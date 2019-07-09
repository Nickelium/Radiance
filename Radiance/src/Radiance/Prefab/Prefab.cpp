#include "pch.h"
#include "Prefab.h"

#include "Radiance/Renderer/API/VertexArray.h"

namespace Radiance
{
	Mesh* CreateCube()
	{

		//VertexArray* vertexArray = _renderDevice->CreateVertexArray();
		//std::vector<float> vertices =
		//{
		//	// front
		//	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		//	 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		//	 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		//	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		//	// back
		//	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		//	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		//	 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		//	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f
		//};
		//VertexBuffer* vertexBuffer = _renderDevice->CreateVertexBuffer(vertices);
		//vertexBuffer->SetLayout
		//({
		//	{DataType::Float3,"a_Pos"},
		//	{DataType::Float2, "a_Tex"}
		//});
		//vertexArray->AddVertexBuffer(vertexBuffer);

		//std::vector<uint32_t> indices2 =
		//{
		//	// front
		//	0, 1, 2,
		//	2, 3, 0,
		//	// right
		//	1, 5, 6,
		//	6, 2, 1,
		//	// back
		//	7, 6, 5,
		//	5, 4, 7,
		//	// left
		//	4, 0, 3,
		//	3, 7, 4,
		//	// bottom
		//	4, 5, 1,
		//	1, 0, 4,
		//	// top
		//	3, 2, 6,
		//	6, 7, 3
		//};
		//IndexBuffer* indexBuffer = _renderDevice->CreateIndexBuffer(indices2);
		//vertexArray->SetIndexBuffer(indexBuffer);

		//TODO
		return new Mesh;
	}

	Mesh* CreateTriangle()
	{
		/*VertexArray* vertexArray = _renderDevice->CreateVertexArray();

		std::vector<float> vertices =
		{
			-0.5f, -0.5f, -0.75f, 1.0f, 0.0f, 1.0f, 1.0f,
			+0.5f, -0.5f, -0.75f, 0.0f, 0.0f, 1.0f, 1.0f,
			+0.0f, +0.5f, -0.75f, 1.0f, 1.0f, 0.0f, 1.0f,
		};
		VertexBuffer* vertexBuffer = _renderDevice->CreateVertexBuffer(vertices);
		BufferLayout layout =
		{
			{DataType::Float3, "a_Position"},
			{DataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		std::vector<unsigned int> indices =
		{
			0, 1, 2
		};
		IndexBuffer* indexBuffer = _renderDevice->CreateIndexBuffer(indices);
		vertexArray->SetIndexBuffer(indexBuffer);*/

		//TODO
		return new Mesh;
	}

}