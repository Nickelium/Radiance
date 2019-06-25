#include "pch.h"
#include "GLBuffer.h"

#include <glad/glad.h>

namespace Radiance
{
	#pragma region VERTEXBUFFER
	GLVertexBuffer::GLVertexBuffer(float* _vertices, uint32_t _nbBytes)
	{
		//Alternative
		//glCreateBuffers(1, &m_RendererID);
		glGenBuffers(1, &m_ID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, _nbBytes, _vertices, GL_STATIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void GLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void GLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	#pragma endregion

	#pragma  region INDEXBUFFER
	GLIndexBuffer::GLIndexBuffer(uint32_t* _indices, uint32_t _count)
		: m_Count(_count)
	{
		glGenBuffers(1, &m_ID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), _indices, GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void GLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void GLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	#pragma endregion
}