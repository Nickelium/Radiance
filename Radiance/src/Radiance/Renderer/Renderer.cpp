#include "pch.h"
#include "Renderer.h"

namespace Radiance
{
	void Renderer::Begin()
	{
	}

	void Renderer::End()
	{
	}

	void Renderer::Submit(VertexArray* _vertexArray)
	{
		_vertexArray->Bind();
		RenderCommand::DrawIndexed(_vertexArray);
	}

}