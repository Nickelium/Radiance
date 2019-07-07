#include "pch.h"
#include "Renderer.h"

#include "API/Shader.h"

namespace Radiance
{
	Renderer::SceneData Renderer::s_SceneData;
	
	void Renderer::Begin(const Camera& _camera)
	{
		s_SceneData.View = _camera.GetViewMatrix();
		s_SceneData.Projection = _camera.GetProjectionMatrix();
		s_SceneData.ViewProjection = _camera.GetViewProjectionMatrix();
	}

	void Renderer::End()
	{
	}

	void Renderer::Submit(Mesh* _mesh)
	{
		_mesh->Bind();
		CommonUniformBinding(_mesh->GetShader());
		RenderCommand::DrawIndexed(_mesh->GetVertexArray());
	}

	void Renderer::CommonUniformBinding(Shader* _shader)
	{
		_shader->SetUniformMat("V", s_SceneData.View);
		_shader->SetUniformMat("P", s_SceneData.Projection);
		_shader->SetUniformMat("VP", s_SceneData.ViewProjection);
	}
}