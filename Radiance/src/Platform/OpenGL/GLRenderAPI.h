#pragma once

#include "Radiance/Renderer/API/RenderAPI.h"

namespace Radiance
{
	class GLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& _color) override;
		virtual void Clear() override;
		virtual void EnableDepth(bool _enable) override;
		virtual void EnableBlend(bool _enable) override;
		virtual void SetViewport(int _x, int _y, int _width, int _height) override;
		virtual void DrawIndexed(VertexArray* _vertexArray) override;

	private:
	};
}
