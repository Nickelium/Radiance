#pragma once

#include "Radiance/Renderer/API/RenderDevice.h"

namespace Radiance
{
	class GLRenderDevice : public RenderDevice
	{
	public:
		virtual ~GLRenderDevice() = default;

		virtual void Init() override {}

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
	};
}
