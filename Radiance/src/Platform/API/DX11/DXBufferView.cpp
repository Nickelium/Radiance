#include "pch.h"
#include "DXBufferView.h"

namespace Radiance
{
	#pragma  region DXRenderTargetBuffer
	DXRenderTargetBuffer::DXRenderTargetBuffer(DXTexture2D* _texture)
		: m_Texture(_texture)
	{
	}

	Texture2D* DXRenderTargetBuffer::GetTexture() const
	{
		return m_Texture;
	}

	DXRenderTargetBuffer::DXRenderTargetBuffer* DXRenderTargetBuffer::CreateInstance(DXRenderDevice* _renderDevice) const
	{
		ID3D11Device* renderDevice = _renderDevice->GetInternalDevice();
		renderDevice->CreateRenderTargetView(m_Texture->GetInternalTexture(), nullptr, &m_RenderTargetView);
		return this;
	}
	#pragma endregion

	#pragma region DXDepthBuffer
	DXDepthBuffer::DXDepthBuffer(DXTexture2D* _texture)
		: m_Texture(_texture)
	{
	}

	Texture2D* DXDepthBuffer::GetTexture() const
	{
		return m_Texture;
	}
	#pragma endregion
}