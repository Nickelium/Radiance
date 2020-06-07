#include "pch.h"
#include "DXDeviceContext.h"

#include "Radiance/Renderer/API/FrameBuffer.h"
#include "DXBufferView.h"

#include "DXIncludes.h"

namespace Radiance
{
	DXDeviceContext::DXDeviceContext(ID3D11DeviceContext* _internalDeviceContext)
		: m_D3D11DeviceContext(_internalDeviceContext)
	{
	}

	DXDeviceContext::~DXDeviceContext()
	{
		m_D3D11DeviceContext->Release();
	}

	void DXDeviceContext::SetClearColor(const glm::vec4& _color)
	{
		m_ClearColor = _color;
	}

	void DXDeviceContext::Clear()
	{
		const float* colorFloats = reinterpret_cast<const float*>(&m_ClearColor);
		ID3D11RenderTargetView* rtView = m_ActiveFrameBuffer->GetDXRTBuffer() ? m_ActiveFrameBuffer->GetDXRTBuffer()->GetD3D11RTView() : nullptr;
		if (rtView)
			m_D3D11DeviceContext->ClearRenderTargetView(rtView, colorFloats);
		uint32_t depthStencilFlags = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL;
		ID3D11DepthStencilView* depthView = m_ActiveFrameBuffer->GetDXDepthBuffer() ? m_ActiveFrameBuffer->GetDXDepthBuffer()->GetD3D11DepthStencilView() : nullptr;
		if(m_DepthEnabled && depthView)
			m_D3D11DeviceContext->ClearDepthStencilView(depthView, depthStencilFlags, 1, 0);
	}

	void DXDeviceContext::EnableDepth(bool _enable)
	{
		m_DepthEnabled = _enable;
	}

	void DXDeviceContext::EnableBlend(bool /*_enable*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXDeviceContext::SetViewport(int _x, int _y, int _width, int _height)
	{
		D3D11_VIEWPORT viewPort;
		memset(&viewPort, 0, sizeof(viewPort));
		viewPort.Width = static_cast<float>(_width);
		viewPort.Height = static_cast<float>(_height);
		viewPort.TopLeftX = static_cast<float>(_x);
		viewPort.TopLeftY = static_cast<float>(_y);
		viewPort.MinDepth = static_cast<float>(0);
		viewPort.MaxDepth = static_cast<float>(1);
		m_D3D11DeviceContext->RSSetViewports(1, &viewPort);
	}

	void DXDeviceContext::DrawIndexed(VertexArray* _vertexArray)
	{
		m_D3D11DeviceContext->DrawIndexed(_vertexArray->GetIndexBuffer()->GetCount(), 0, 0);
	}

	void DXDeviceContext::SetFrameBuffer(FrameBuffer* _frameBuffer)
	{
		DXFrameBuffer* dxFrameBuffer = dynamic_cast<DXFrameBuffer*>(_frameBuffer);
		RAD_ASSERT(dxFrameBuffer, "DXDeviceContext only compatible with DXFrameBuffer");

		m_ActiveFrameBuffer = dxFrameBuffer;

		ID3D11RenderTargetView* rtArray = m_ActiveFrameBuffer->GetDXRTBuffer() ? m_ActiveFrameBuffer->GetDXRTBuffer()->GetD3D11RTView() : nullptr;
		ID3D11DepthStencilView* depthStencilView = m_ActiveFrameBuffer->GetDXDepthBuffer() ? m_ActiveFrameBuffer->GetDXDepthBuffer()->GetD3D11DepthStencilView() : nullptr;
		m_D3D11DeviceContext->OMSetRenderTargets(1, &rtArray, depthStencilView);
	}

	DXDeviceContext* GetDXDeviceContext()
	{
		RAD_ASSERT(dynamic_cast<DXDeviceContext*>(Locator::Get<DeviceContext>()), "DeviceContext is not of type DXDeviceContext");
		return dynamic_cast<DXDeviceContext*>(Locator::Get<DeviceContext>());
	}

}
