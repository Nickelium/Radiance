#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

#include "DeviceFactory.h"
/**
 * Represent abstraction of OpenGL and D3D11
 */

/**
 * RenderAPI is a virtual (interface) to utilize runtime polymorphism between the different implementations
   But in the end these represent wrappers around raw implementation calls, which are actually static function calls.
   Therefore RenderCommand is called statically.
 */
namespace Radiance
{
	struct API
	{
		struct Data
		{
			std::string vendor;
			std::string renderer;
			std::string version;
		};

		API(RenderAPI _type) : type(_type) {}
		RenderAPI type;
		Data data;
	};
	class FrameBuffer;
	class DeviceContext : public Service
	{
	public:
		virtual void SetClearColor(const glm::vec4& _color) = 0;
		virtual void Clear() = 0;
		virtual void EnableDepth(bool _enable) = 0;
		virtual void EnableBlend(bool _enable) = 0;
		virtual void SetViewport(int _x, int _y, int _width, int _height) = 0;
		virtual void SetFrameBuffer(FrameBuffer* _frameBuffer) = 0;

		virtual void DrawIndexed(VertexArray* _vertexArray) = 0;

		SERVICE_CLASS(DeviceContext)
	};
}
