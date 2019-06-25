#pragma once

#include "Radiance/Renderer/RenderAPI.h"

namespace Radiance
{
	class GLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& _color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(VertexArray* _vertexArray) override;

	private:
	};
}
