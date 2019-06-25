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

	VertexBuffer* GLRenderDevice::CreateVertexBuffer(std::vector<float> _vertices) const
	{
		return new GLVertexBuffer(_vertices);
	}

	IndexBuffer* GLRenderDevice::CreateIndexBuffer(std::vector<uint32_t> _indices) const
	{
		return new GLIndexBuffer(_indices);
	}

	Shader* GLRenderDevice::CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const
	{
		return new GLShader(_vertexSource, _fragmentSource);
	}

}