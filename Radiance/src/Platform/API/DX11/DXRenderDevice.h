#pragma once

#include "Radiance/Renderer/API/RenderDevice.h"

struct ID3D11Device;
struct ID3D11Texture2D;

namespace Radiance
{
	class DXTexture2D;
	class DXRTBuffer;
	class DXDepthBuffer;
	class DXFrameBuffer;


	class DXRenderDevice : public RenderDevice
	{
	public:
		DXRenderDevice(ID3D11Device* _internalDevice);
		virtual ~DXRenderDevice();

		virtual void Init() override;

		virtual VertexArray* CreateVertexArray() const override;
		virtual VertexBuffer* CreateVertexBuffer(std::vector<float> _vertices) const override;
		virtual IndexBuffer* CreateIndexBuffer(std::vector<uint32_t> _indices) const override;
		virtual Shader* CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const override;

		virtual Texture2D* CreateTexture2D(const std::string& _filePath) const override;
		virtual Texture2D* CreateTexture2D(int _width, int _height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const override;
		virtual RTBuffer* CreateRTBuffer(int _width, int _height) const override;
		virtual RTBuffer* CreateRTBuffer(Texture2D* _texture) const;
		virtual DepthBuffer* CreateDepthBuffer(int _width, int _height) const override;
		virtual FrameBuffer* CreateFrameBuffer(int _width, int _height) const override;
		virtual FrameBuffer* CreateFrameBuffer(RTBuffer* _rtBuffer, DepthBuffer* _depthBuffer) const override;
		virtual GPUTimer* CreateGPUTimer() const override;

	public:
		/*DXVertexArray* CreateInternalVertexArray() const;
		DXVertexBuffer* CreateInternalVertexBuffer(std::vector<float> _vertices) const;
		DXIndexBuffer* CreateInternalIndexBuffer(std::vector<uint32_t> _indices) const;
		DXShader* CreateInternalShader(const std::string& _vertexSource, const std::string& _fragmentSource) const;*/
		DXTexture2D* CreateInternalTexture2D(ID3D11Texture2D* _d3d11Texture2D) const;
		DXTexture2D* CreateInternalTexture2D(const std::string& _filePath) const;
		DXTexture2D* CreateInternalTexture2D(int _width, int _height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const;

		DXRTBuffer* CreateInternalRTBuffer(int _width, int _height) const;
		DXRTBuffer* CreateInternalRTBuffer(DXTexture2D* _texture) const;
		DXDepthBuffer* CreateInternalDepthBuffer(int _width, int _height) const;
		DXFrameBuffer* CreateInternalFrameBuffer(int _width, int _height) const;
		//DXGPUTimer* CreateInternalGPUTimer() const;
	
		//DXTexture2D* CreateInternalTexture2D(int _width, int height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const;
		//DXTexture2D* CreateInternalTexture2D(int _width, int height, FormatUsage _usage) const;


		ID3D11Device* GetD3D11Device() const;
	private:
		ID3D11Device* m_D3D11RenderDevice = nullptr;
	};

	DXRenderDevice* GetDXRenderDevice();
}