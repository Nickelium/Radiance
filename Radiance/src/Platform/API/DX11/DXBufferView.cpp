#include "pch.h"
#include "DXBufferView.h"

#include "DXRenderDevice.h"
#include "DXDeviceContext.h"
#include "DXTexture.h"

#include "DXIncludes.h"

namespace Radiance
{
	#pragma  region DXRenderTargetBuffer
	DXRTBuffer::DXRTBuffer(DXTexture2D* _texture)
		: m_Texture(_texture)
	{
		CreateInternals();
	}

	DXRTBuffer::~DXRTBuffer()
	{
		delete m_Texture;
		m_D3D11RenderTargetView->Release();
	}

	Texture2D* DXRTBuffer::GetTexture() const
	{
		return m_Texture;
	}

	void DXRTBuffer::SetSize(int /*_width*/, int /*_height*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXRTBuffer::CreateInternals()
	{
		DXRenderDevice* renderDevice = GetDXRenderDevice();
		ID3D11Device* d3d11RenderDevice = renderDevice->GetD3D11Device();
		d3d11RenderDevice->CreateRenderTargetView(m_Texture->GetD3D11Texture(), nullptr, &m_D3D11RenderTargetView);
	}
	#pragma endregion

	#pragma region DXDepthBuffer
	DXDepthBuffer::DXDepthBuffer(DXTexture2D* _texture)
		: m_Texture(_texture)
	{
		CreateInternals();
	}

	DXDepthBuffer::~DXDepthBuffer()
	{
		delete m_Texture;
		m_D3D11DepthStencilView->Release();
	}

	Texture2D* DXDepthBuffer::GetTexture() const
	{
		return m_Texture;
	}

	void DXDepthBuffer::SetSize(int /*_width*/, int /*_height*/)
	{
	}

	void DXDepthBuffer::CreateInternals()
	{
		DXRenderDevice* renderDevice = GetDXRenderDevice();
		ID3D11Device* d3d11RenderDevice = renderDevice->GetD3D11Device();
		d3d11RenderDevice->CreateDepthStencilView(m_Texture->GetD3D11Texture(), nullptr, &m_D3D11DepthStencilView);
	}

#pragma endregion

	DXFrameBuffer::DXFrameBuffer(int _width, int _height)
		: m_Width(_width), m_Height(_height)
	{

	}

	DXFrameBuffer::DXFrameBuffer(DXRTBuffer* _rtBuffer, DXDepthBuffer* _depthBuffer)
		: m_RTBuffer(_rtBuffer), m_DepthBuffer(_depthBuffer)
	{
	}

	DXFrameBuffer::~DXFrameBuffer()
	{
		delete m_RTBuffer;
		delete m_DepthBuffer;
	}

	void DXFrameBuffer::SetSize(int _width, int _height)
	{
		m_Width = _width;
		m_Height = _height;
	}

	void DXFrameBuffer::Bind() const
	{
		DXDeviceContext* dc = GetDXDeviceContext();
		ID3D11DeviceContext* d3d11DC = dc->GetD3D11DeviceContext();
		ID3D11RenderTargetView* rtArray = GetDXRTBuffer()->GetD3D11RTView();
		// Can bind multiple rendertarget for example deferred renderer
		d3d11DC->OMSetRenderTargets(1, &rtArray, GetDXDepthBuffer()->GetD3D11DepthStencilView());
	}

	void DXFrameBuffer::UnBind() const
	{
		DXDeviceContext* dc = GetDXDeviceContext();
		ID3D11DeviceContext* d3d11DC = dc->GetD3D11DeviceContext();
		ID3D11RenderTargetView* rtArray = nullptr;
		d3d11DC->OMSetRenderTargets(1, &rtArray, nullptr);
	}

	RTBuffer* DXFrameBuffer::GetRTBuffer() const
	{
		return m_RTBuffer;
	}

	DepthBuffer* DXFrameBuffer::GetDepthBuffer() const
	{
		return m_DepthBuffer;
	}

	DXRTBuffer* DXFrameBuffer::GetDXRTBuffer() const
	{
		return m_RTBuffer;
	}

	DXDepthBuffer* DXFrameBuffer::GetDXDepthBuffer() const
	{
		return m_DepthBuffer;
	}

}