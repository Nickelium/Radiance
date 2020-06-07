#include "pch.h"
#include "GLRenderDevice.h"

#include "GLVertexArray.h"
#include "GLBuffer.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLFrameBuffer.h"
#include "GLGPUTimer.h"

#include "GLDeviceContext.h"

#include "GLInclude.h"

namespace Radiance
{		
	VertexArray* GLRenderDevice::CreateVertexArray() const
	{
		return CreateInternalVertexArray();
	}

	VertexBuffer* GLRenderDevice::CreateVertexBuffer(std::vector<float> _vertices) const
	{
		return CreateInternalVertexBuffer(_vertices);
	}

	IndexBuffer* GLRenderDevice::CreateIndexBuffer(std::vector<uint32_t> _indices) const
	{
		return CreateInternalIndexBuffer(_indices);
	}

	Shader* GLRenderDevice::CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const
	{
		//Preprocess Includes
		return CreateInternalShader(_vertexSource, _fragmentSource);
	}

	Texture2D* GLRenderDevice::CreateTexture2D(const std::string& _filePath) const
	{
		return CreateInternalTexture2D(_filePath);
	}

	Texture2D* GLRenderDevice::CreateTexture2D(int _width, int _height, FormatUsage _usage) const
	{
		return CreateInternalTexture2D(_width, _height, _usage);
	}

	RTBuffer* GLRenderDevice::CreateRTBuffer(int _width, int _height) const
	{
		return CreateInternalRTBuffer(_width, _height);
	}

	RTBuffer* GLRenderDevice::CreateRTBuffer(Texture2D* /*_texture*/) const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DepthBuffer* GLRenderDevice::CreateDepthBuffer(int _width, int _height) const
	{
		return CreateInternalDepthBuffer(_width, _height);
	}

	FrameBuffer* GLRenderDevice::CreateFrameBuffer(int _width, int _height) const
	{
		return CreateInternalFrameBuffer(_width, _height);
	}

	Radiance::FrameBuffer* GLRenderDevice::CreateFrameBuffer(RTBuffer* /*_rtBuffer*/, DepthBuffer* /*_depthBuffer*/) const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	GPUTimer* GLRenderDevice::CreateGPUTimer() const
	{
		return CreateInternalGPUTimer();
	}

#pragma region INTERNAL
	GLVertexArray* GLRenderDevice::CreateInternalVertexArray() const
	{
		return new GLVertexArray;
	}

	GLVertexBuffer* GLRenderDevice::CreateInternalVertexBuffer(std::vector<float> _vertices) const
	{
		return new GLVertexBuffer(_vertices);
	}

	GLIndexBuffer* GLRenderDevice::CreateInternalIndexBuffer(std::vector<uint32_t> _indices) const
	{
		return new GLIndexBuffer(_indices);
	}

	GLShader* GLRenderDevice::CreateInternalShader(const std::string& _vertexSource, const std::string& _fragmentSource) const
	{
		return new GLShader(_vertexSource, _fragmentSource);
	}

	GLTexture2D* GLRenderDevice::CreateInternalTexture2D(const std::string& _filePath) const
	{
		return new GLTexture2D(_filePath);
	}

	GLTexture2D* GLRenderDevice::CreateInternalTexture2D(int _width, int _height, FormatUsage _usage /*= FormatUsage::COLOR_BUFFER*/) const
	{
		return new GLTexture2D(_width, _height, _usage);
	}

	GLRTBuffer* GLRenderDevice::CreateInternalRTBuffer(int _width, int _height) const
	{
		return new GLRTBuffer(_width, _height);
	}

	GLDepthBuffer* GLRenderDevice::CreateInternalDepthBuffer(int _width, int _height) const
	{
		return new GLDepthBuffer(_width, _height);
	}

	GLFrameBuffer* GLRenderDevice::CreateInternalFrameBuffer(int _width, int _height) const
	{
		return new GLFrameBuffer(_width, _height);
	}

	GLGPUTimer* GLRenderDevice::CreateInternalGPUTimer() const
	{
		return new GLGPUTimer;
	}
#pragma endregion
}