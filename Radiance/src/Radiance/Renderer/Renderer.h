#pragma once

#include "API/Shader.h"
#include "Material.h"
#include "Camera/Camera.h"
#include "MeshRender.h"

namespace Radiance
{
	class FrameBuffer;
	class Renderer
	{
	public:
		static void Begin(const Camera& _camera);
		static void End();

		static void Submit(MeshRender* _mesh, const glm::mat4& _transform);
	private:
		static void CommonUniformBinding(Shader* _shader);

		struct SceneData
		{
			glm::mat4 View;
			glm::mat4 Projection;
			glm::mat4 ViewProjection;

			glm::vec3 CameraPos;
		};
		static SceneData s_SceneData;
	};
}
