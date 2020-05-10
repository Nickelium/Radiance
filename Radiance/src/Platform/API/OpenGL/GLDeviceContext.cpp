#include "pch.h"
#include "GLDeviceContext.h"

#include <glad/glad.h>

namespace Radiance
{
	void GLDeviceContext::SetClearColor(const glm::vec4& _color)
	{
		glClearColor(_color.r, _color.g, _color.b, _color.a );
		//TEMP
		glDisable(GL_CULL_FACE);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}

	void GLDeviceContext::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void GLDeviceContext::EnableDepth(bool _enable)
	{
		if (_enable)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void GLDeviceContext::EnableBlend(bool _enable)
	{
		if (_enable)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendEquation(GL_FUNC_ADD);
		}
		else
			glDisable(GL_BLEND);
	}

	void GLDeviceContext::SetViewport(int _x, int _y, int _width, int _height)
	{
		glViewport(_x, _y, _width, _height);
	}

	void GLDeviceContext::DrawIndexed(VertexArray* _vertexArray)
	{
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}