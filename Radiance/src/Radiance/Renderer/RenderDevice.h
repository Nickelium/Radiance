#pragma once

namespace Radiance
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class RenderDevice
	{
	public:
		virtual ~RenderDevice() = default;

		virtual VertexArray* CreateVertexArray() const = 0;
		virtual VertexBuffer* CreateVertexBuffer(float* _vertices, uint32_t _nbBytes) const = 0;
		virtual IndexBuffer* CreateIndexBuffer(uint32_t* _indices, uint32_t _nbBytes) const = 0;

		virtual Shader* CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const = 0;

		static RenderDevice* Create();
	};
}
