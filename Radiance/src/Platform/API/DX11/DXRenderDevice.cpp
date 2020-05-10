#include "pch.h"
#include "DXRenderDevice.h"

#include "DXIncludes.h"

namespace Radiance
{
	DXRenderDevice::DXRenderDevice(ID3D11Device* _d3d11Device)
		: m_D3D11Device(_d3d11Device)
	{
	}

	void DXRenderDevice::Init()
	{
	
	}

	VertexArray* DXRenderDevice::CreateVertexArray() const
	{
		return nullptr;
	}

	VertexBuffer* DXRenderDevice::CreateVertexBuffer(std::vector<float> /*_vertices*/) const
	{
		return nullptr;
	}

	IndexBuffer* DXRenderDevice::CreateIndexBuffer(std::vector<uint32_t> /*_indices*/) const
	{
		return nullptr;
	}

	Shader* DXRenderDevice::CreateShader(const std::string& /*_vertexSource*/, const std::string& /*_fragmentSource*/) const
	{
		return nullptr;
	}

	RenderTargetBuffer* DXRenderDevice::CreateRTBuffer(int /*_width*/, int /*_height*/) const
	{
		DXTexture2D* texture = CreateInternalTexture2D(0, 0);
		DXRenderTargetBuffer* renderTargetBuffer = new DXRenderTargetBuffer(texture);
		return renderTargetBuffer->CreateInstance(this);
	}

	DepthBuffer* DXRenderDevice::CreateDepthBuffer(int /*_width*/, int /*_height*/) const
	{
		//throw std::logic_error("The method or operation is not implemented.");
		return nullptr;
	}

	Texture2D* DXRenderDevice::CreateTexture2D(const std::string& /*_filePath*/) const
	{
		return nullptr;
	}

	Texture2D* DXRenderDevice::CreateTexture2D(int _width, int _height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const
	{
		return CreateInternalTexture2D(_width, _height, _usage);
	}

	FrameBuffer* DXRenderDevice::CreateFrameBuffer(int /*_width*/, int /*_height*/) const
	{
		return nullptr;
	}

	GPUTimer* DXRenderDevice::CreateGPUTimer() const
	{
		return nullptr;
	}

	DXTexture2D* DXRenderDevice::CreateInternalTexture2D(int _width, int _height, FormatUsage _usage /*= FormatUsage::COLOR_BUFFER*/) const
	{
		return new DXTexture2D(_width, _height);
	}

	ID3D11Device* DXRenderDevice::GetInternalDevice() const
	{
		return m_D3D11Device;
	}
}