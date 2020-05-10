#pragma once

#include "Radiance/Renderer/API/BufferView.h"

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace Radiance
{
	class Texture2D;
	class DXTexture2D;

	class DXRenderTargetBuffer : public RenderTargetBuffer
	{
	public:
		DXRenderTargetBuffer(DXTexture2D* _texture);
		virtual Texture2D* GetTexture() const override;

		DXRenderTargetBuffer* CreateInstance(DXRenderDevice* _renderDevice) const;
	private:
		DXTexture2D* m_Texture = nullptr;
		ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	};

	class DXDepthBuffer : public DepthBuffer
	{
	public:
		DXDepthBuffer(DXTexture2D* _texture);
		virtual Texture2D* GetTexture() const override;

		DXDepthBuffer* CreateInstance(DXDepthBuffer* _depthBuffer) const;
	private:
		DXTexture2D* m_Texture = nullptr;
		ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	};
}
