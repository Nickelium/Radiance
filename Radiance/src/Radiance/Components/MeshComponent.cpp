#include "pch.h"
#include "MeshComponent.h"

#include "Radiance/Renderer/Mesh.h"

namespace Radiance
{

	MeshComponent::MeshComponent(Actor* _actor, Mesh* _mesh)
		: Component(_actor), m_Mesh(_mesh)
	{
	}

	MeshComponent::~MeshComponent()
	{
		delete m_Mesh;
	}

}