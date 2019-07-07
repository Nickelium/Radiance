#pragma once

#include "Component.h"

namespace Radiance
{
	class Mesh;
	class MeshComponent : public Component
	{
	public:
		MeshComponent(Actor* _actor, Mesh* _mesh);
		virtual ~MeshComponent();

		inline Mesh* GetMesh() const { return m_Mesh; }

		COMPONENT_CLASS(MeshComponent)
	private:
		Mesh* m_Mesh;
	};
}
