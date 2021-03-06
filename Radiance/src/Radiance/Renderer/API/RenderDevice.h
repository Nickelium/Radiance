#pragma once

#include "Radiance/Core/Locator.h"

#include "Texture2D.h"

/**
 * Responsible through resources creation (Abstract factory)
   Each API as an implementation of the RenderDevice
 */
namespace Radiance
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class FrameBuffer;
	class GPUTimer;

	class RenderDevice : public Service
	{
	public:
		virtual ~RenderDevice() = default;

		virtual VertexArray* CreateVertexArray() const = 0;
		virtual VertexBuffer* CreateVertexBuffer(std::vector<float> _vertices) const = 0;
		virtual IndexBuffer* CreateIndexBuffer(std::vector<uint32_t> _indices) const = 0;

		virtual Shader* CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const = 0;

		virtual Texture2D* CreateTexture2D(const std::string& _filePath) const = 0;
		virtual Texture2D* CreateTexture2D(int _width, int _height, FormatUsage _usage = FormatUsage::COLOR_BUFFER) const = 0;

		virtual FrameBuffer* CreateFrameBuffer(int _width, int _height) const = 0;

		virtual GPUTimer* CreateGPUTimer() const = 0;

		static RenderDevice* Create();

		SERVICE_CLASS(RenderDevice)
	};
}
