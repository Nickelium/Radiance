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
		
		inline static void EnableDepth(bool _enable)
		{
			s_RenderAPI->EnableDepth(_enable);
		}

		inline static void EnableBlend(bool _enable)
		{
			s_RenderAPI->EnableBlend(_enable);
		}

		inline static void SetViewport(int _x, int _y, int _width, int _height)
		{
			s_RenderAPI->SetViewport(_x, _y, _width, _height);
		}

		inline static void DrawIndexed(VertexArray* _vertexArray)
		{
			s_RenderAPI->DrawIndexed(_vertexArray);
		}
	private:
		static std::unique_ptr<RenderAPI> s_RenderAPI;
	};
}
