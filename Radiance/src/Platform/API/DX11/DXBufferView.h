#pragma once

#include "Radiance/Renderer/API/BufferView.h"
#include "Radiance/Renderer/API/FrameBuffer.h"
#include "DXRenderDevice.h"

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace Radiance
{
	class Texture2D;
	class DXTexture2D;

	class DXRTBuffer : public RTBuffer
	{
	public:
		DXRTBuffer(DXTexture2D* _texture);
		virtual ~DXRTBuffer();

		virtual Texture2D* GetTexture() const override;
		virtual void SetSize(int _width, int _height) override;

	public:
		DXTexture2D* GetDXTexture() const { return m_Texture; }
		ID3D11RenderTargetView* GetD3D11RTView() const { return m_D3D11RenderTargetView; }
	private:
		void CreateInternals();
		DXTexture2D* m_Texture = nullptr;
		ID3D11RenderTargetView* m_D3D11RenderTargetView = nullptr;
	};

	class DXDepthBuffer : public DepthBuffer
	{
	public:
		DXDepthBuffer(DXTexture2D* _texture);
		virtual ~DXDepthBuffer();

		virtual Texture2D* GetTexture() const override;
		virtual void SetSize(int _width, int _height) override;
	public:
		DXTexture2D* GetDXTexture() const { return m_Texture; }
		ID3D11DepthStencilView* GetD3D11DepthStencilView() const { return m_D3D11DepthStencilView; }
	private:
		void CreateInternals();
		DXTexture2D* m_Texture = nullptr;
		ID3D11DepthStencilView* m_D3D11DepthStencilView = nullptr;
	};

	class DXFrameBuffer : public FrameBuffer
	{
	public:
		DXFrameBuffer(DXRTBuffer* _rtBuffer, DXDepthBuffer* _depthBuffer);
		DXFrameBuffer(int _width, int _height);
		virtual ~DXFrameBuffer();
		
		virtual void SetSize(int _width, int _height) override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual RTBuffer* GetRTBuffer() const override;
		virtual DepthBuffer* GetDepthBuffer() const override;
	public:
		DXRTBuffer* GetDXRTBuffer() const;
		DXDepthBuffer* GetDXDepthBuffer() const;
	private:
		int m_Width;
		int m_Height;

		DXRTBuffer* m_RTBuffer;
		DXDepthBuffer* m_DepthBuffer;
	};
}
