#include "pch.h"
#include "Renderer.h"

#include "Radiance/Renderer/API/DeviceContext.h"
#include "Radiance/Renderer/API/DeviceFactory.h"
#include "API/Shader.h"

Radiance::RenderAPI Radiance::API = Radiance::RenderAPI::NONE;

namespace Radiance
{
	Renderer::SceneData Renderer::s_SceneData;
	
	void Renderer::Begin(const Camera& _camera)
	{
		s_SceneData.View = _camera.GetViewMatrix();
		s_SceneData.Projection = _camera.GetProjectionMatrix();
		s_SceneData.ViewProjection = _camera.GetViewProjectionMatrix();
		s_SceneData.CameraPos = _camera.GetPosition();
	}

	void Renderer::End()
	{
	}

	void Renderer::Submit(MeshRender* _mesh, const glm::mat4& _transform)
	{
		_mesh->Bind();
		Shader* shader = _mesh->GetMaterial()->GetShader();
		CommonUniformBinding(shader);
		shader->SetUniform("M", _transform);
		Locator::Get<DeviceContext>()->DrawIndexed(_mesh->GetVertexArray());
	}

	void Renderer::CommonUniformBinding(Shader* _shader)
	{
		_shader->SetUniform("V", s_SceneData.View);
		_shader->SetUniform("P", s_SceneData.Projection);
		_shader->SetUniform("CameraPos", s_SceneData.CameraPos);
		//_shader->SetUniform("VP", s_SceneData.ViewProjection);
	}
}