#include "pch.h"
#include "DXRenderDevice.h"

#include "DXIncludes.h"

#include "DXTexture.h"
#include "DXBufferView.h"

namespace Radiance
{
#pragma region PUBLIC
	DXRenderDevice::DXRenderDevice(ID3D11Device* _d3d11Device)
		: m_D3D11RenderDevice(_d3d11Device)
	{
		Init();
	}

	DXRenderDevice::~DXRenderDevice()
	{
		m_D3D11RenderDevice->Release();
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

	RTBuffer* DXRenderDevice::CreateRTBuffer(int _width, int _height) const
	{
		//DXTexture2D* texture = nullptr;// CreateInternalTexture2D(0, 0);
		//DXRenderTargetBuffer* renderTargetBuffer = new DXRenderTargetBuffer(texture);
		//return renderTargetBuffer->CreateInstance(this);
		//return nullptr;
		return CreateInternalRTBuffer(_width, _height);
	}

	RTBuffer* DXRenderDevice::CreateRTBuffer(Texture2D* _texture) const
	{
		DXTexture2D* dxTexture = dynamic_cast<DXTexture2D*>(_texture);
		RAD_ASSERT(dxTexture, "");
		return CreateInternalRTBuffer(dxTexture);
	}

	DepthBuffer* DXRenderDevice::CreateDepthBuffer(int _width, int _height) const
	{
		//throw std::logic_error("The method or operation is not implemented.");
		//return nullptr;
		return CreateInternalDepthBuffer(_width, _height);
	}

	Texture2D* DXRenderDevice::CreateTexture2D(const std::string& _filePath) const
	{
		//return nullptr;
		return CreateInternalTexture2D(_filePath);
	}

	Texture2D* DXRenderDevice::CreateTexture2D(int _width, int _height, FormatUsage _usage) const
	{
		//return nullptr;
		return CreateInternalTexture2D(_width, _height, _usage);
	}

	FrameBuffer* DXRenderDevice::CreateFrameBuffer(int _width, int _height) const
	{
		//return nullptr;
		return CreateInternalFrameBuffer(_width, _height);
	}

	FrameBuffer* DXRenderDevice::CreateFrameBuffer(RTBuffer* _rtBuffer, DepthBuffer* _depthBuffer) const
	{
		DXRTBuffer* dxRTBuffer = dynamic_cast<DXRTBuffer*>(_rtBuffer);
		DXDepthBuffer* dxDepthBuffer = dynamic_cast<DXDepthBuffer*>(_depthBuffer);
		return new DXFrameBuffer(dxRTBuffer, dxDepthBuffer);
	}

	GPUTimer* DXRenderDevice::CreateGPUTimer() const
	{
		return nullptr;
	}
#pragma endregion

#pragma region INTERNAL
	DXTexture2D* DXRenderDevice::CreateInternalTexture2D(ID3D11Texture2D* d3d11Texture2D) const
	{
		return new DXTexture2D(d3d11Texture2D);
	}

	DXTexture2D* DXRenderDevice::CreateInternalTexture2D(const std::string& /*_filePath*/) const
	{
		return nullptr;
	}

	DXTexture2D* DXRenderDevice::CreateInternalTexture2D(int _width, int _height, FormatUsage _usage /*= FormatUsage::COLOR_BUFFER*/) const
	{
		return new DXTexture2D(_width, _height, _usage);
	}

	DXRTBuffer* DXRenderDevice::CreateInternalRTBuffer(int /*_width*/, int /*_height*/) const
	{
		return nullptr;
	}

	DXRTBuffer* DXRenderDevice::CreateInternalRTBuffer(DXTexture2D* _texture) const
	{
		return new DXRTBuffer(_texture);
	}

	DXDepthBuffer* DXRenderDevice::CreateInternalDepthBuffer(int /*_width*/, int /*_height*/) const
	{
		return nullptr;
	}

	DXFrameBuffer* DXRenderDevice::CreateInternalFrameBuffer(int /*_width*/, int /*_height*/) const
	{
		return nullptr;
	}

	//DXTexture2D* DXRenderDevice::CreateInternalTexture2D(int /*_width*/, int /*height*/, FormatUsage /*_usage*/ /*= FormatUsage::COLOR_BUFFER*/) const
	//{
	//	return nullptr;
	//}

	//DXTexture2D* DXRenderDevice::CreateInternalTexture2D(int _width, int _height, FormatUsage _usage /*= FormatUsage::COLOR_BUFFER*/) const
	//{
	//	return new DXTexture2D(_width, _height);
	//}

	ID3D11Device* DXRenderDevice::GetD3D11Device() const
	{
		return m_D3D11RenderDevice;
	}

	Radiance::DXRenderDevice* GetDXRenderDevice()
	{
		RAD_ASSERT(dynamic_cast<DXRenderDevice*>(Locator::Get<RenderDevice>()), "RenderDevice is not of type DXRenderDevice");
		return dynamic_cast<DXRenderDevice*>(Locator::Get<RenderDevice>());
	}

#pragma endregion
}