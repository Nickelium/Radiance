#include "pch.h"
#include "GLRenderDevice.h"

#include "GLVertexArray.h"
#include "GLBuffer.h"
#include "GLShader.h"

namespace Radiance
{
	VertexArray* GLRenderDevice::CreateVertexArray() const
	{
		return new GLVertexArray;
	}

	VertexBuffer* GLRenderDevice::CreateVertexBuffer(float* _vertices, uint32_t _nbBytes) const
	{
		return new GLVertexBuffer(_vertices, _nbBytes);
	}

	IndexBuffer* GLRenderDevice::CreateIndexBuffer(uint32_t* _indices, uint32_t _nbBytes) const
	{
		return new GLIndexBuffer(_indices, _nbBytes);
	}

	Shader* GLRenderDevice::CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const
	{
		return new GLShader(_vertexSource, _fragmentSource);
	}

}