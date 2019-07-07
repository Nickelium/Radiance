#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace Radiance
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	class Actor;
	class TransformComponent : public Component
	{
	public:
		TransformComponent(Actor* _actor);

		COMPONENT_CLASS(TransformComponent)
	private:
		Transform m_Transform;
	};
}
