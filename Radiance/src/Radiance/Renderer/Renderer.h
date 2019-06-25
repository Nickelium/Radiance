#pragma once

#include "RenderCommand.h"

namespace Radiance
{
	class Renderer
	{
	public:
		static void Begin();
		static void End();

		static void Submit(VertexArray* _vertexArray);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); };
	private:
	};
}
