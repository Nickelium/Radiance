#pragma once

#include "Radiance/Renderer/API/RenderDevice.h"

struct ID3D11Device;

namespace Radiance
{
	class DXRenderDevice : public RenderDevice
	{
	public:
		DXRenderDevice(ID3D11Device* _internalDevice);
		virtual ~DXRenderDevice() = default;

		virtual void Init() override;

		virtual VertexArray* CreateVertexArray() const override;
		virtual VertexBuffer* CreateVertexBuffer(std::vector<float> _vertices) const override;
		virtual IndexBuffer* CreateIndexBuffer(std::vector<uint32_t> _indices) const override;
		virtual Shader* CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const override;

		virtual Texture2D* CreateTexture2D(const std::string& _filePath) const override;
		virtual Texture2D* CreateTexture2D(int _width, int _height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const override;
		virtual RenderTargetBuffer* CreateRTBuffer(int _width, int _height) const override;
		virtual DepthBuffer* CreateDepthBuffer(int _width, int _height) const override;
		virtual FrameBuffer* CreateFrameBuffer(int _width, int _height) const override;
		virtual GPUTimer* CreateGPUTimer() const override;

		DXTexture2D* CreateInternalTexture2D(int _width, int height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const;

		ID3D11Device* GetInternalDevice() const;
	private:
		ID3D11Device* m_D3D11Device = nullptr;
	};
}