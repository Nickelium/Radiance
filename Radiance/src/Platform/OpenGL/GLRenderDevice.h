#pragma once

#include "Radiance/Renderer/RenderDevice.h"

namespace Radiance
{
	class GLRenderDevice : public RenderDevice
	{
	public:
		virtual ~GLRenderDevice() = default;

		virtual VertexArray* CreateVertexArray() const override;
		virtual VertexBuffer* CreateVertexBuffer(float* _vertices, uint32_t _nbBytes) const override;
		virtual IndexBuffer* CreateIndexBuffer(uint32_t* _indices, uint32_t _nbBytes) const override;
		virtual Shader* CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const override;

	};
}
