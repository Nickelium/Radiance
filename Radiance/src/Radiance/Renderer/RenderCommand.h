#pragma once

#include "RenderAPI.h"

namespace Radiance
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& _color)
		{
			s_RenderAPI->SetClearColor(_color);
		}
		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}
		inline static void DrawIndexed(VertexArray* _vertexArray)
		{
			s_RenderAPI->DrawIndexed(_vertexArray);
		}
	private:
		static std::unique_ptr<RenderAPI> s_RenderAPI;
	};
}
