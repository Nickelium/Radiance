#include "pch.h"
#include "GLRenderAPI.h"

#include <glad/glad.h>

namespace Radiance
{
	void GLRenderAPI::SetClearColor(const glm::vec4& _color)
	{
		glClearColor(_color.r, _color.g, _color.b, _color.a );
	}

	void GLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void GLRenderAPI::DrawIndexed(VertexArray* _vertexArray)
	{
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}