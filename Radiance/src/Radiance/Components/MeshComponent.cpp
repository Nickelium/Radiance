#include "pch.h"
#include "MeshComponent.h"

#include "Radiance/Renderer/MeshRender.h"

namespace Radiance
{

	MeshComponent::MeshComponent(Actor* _actor, MeshRender* _mesh)
		: Component(_actor), m_Mesh(_mesh)
	{
	}

	MeshComponent::~MeshComponent()
	{
		delete m_Mesh;
	}

}