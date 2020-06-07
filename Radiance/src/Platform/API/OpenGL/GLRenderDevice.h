#pragma once

#include "Radiance/Renderer/API/RenderDevice.h"

#include "GLForwardDecl.h"

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

		virtual RTBuffer* CreateRTBuffer(int _width, int _height) const override;
		virtual RTBuffer* CreateRTBuffer(Texture2D* _texture) const override;
		virtual DepthBuffer* CreateDepthBuffer(int _width, int _height) const override;
		virtual FrameBuffer* CreateFrameBuffer(int _width, int _height) const override;
		virtual FrameBuffer* CreateFrameBuffer(RTBuffer* _rtBuffer, DepthBuffer* _depthBuffer) const override;
		virtual GPUTimer* CreateGPUTimer() const override;

	public:
		GLVertexArray* CreateInternalVertexArray() const;
		GLVertexBuffer* CreateInternalVertexBuffer(std::vector<float> _vertices) const;
		GLIndexBuffer* CreateInternalIndexBuffer(std::vector<uint32_t> _indices) const;
		GLShader* CreateInternalShader(const std::string& _vertexSource, const std::string& _fragmentSource) const;
		GLTexture2D* CreateInternalTexture2D(const std::string& _filePath) const;
		GLTexture2D* CreateInternalTexture2D(int _width, int _height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const;

		GLRTBuffer* CreateInternalRTBuffer(int _width, int _height) const;
		GLDepthBuffer* CreateInternalDepthBuffer(int _width, int _height) const;
		GLFrameBuffer* CreateInternalFrameBuffer(int _width, int _height) const;
		GLGPUTimer* CreateInternalGPUTimer() const;
	};

	inline GLRenderDevice* GetGLRenderDevice()
	{
		RAD_ASSERT(dynamic_cast<GLRenderDevice*>(Locator::Get<RenderDevice>()), "RenderDevice is not of type GLRenderDevice");
		return dynamic_cast<GLRenderDevice*>(Locator::Get<RenderDevice>());
	}


}
