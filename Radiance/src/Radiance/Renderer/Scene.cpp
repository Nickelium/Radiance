#include "pch.h"
#include "Scene.h"

namespace Radiance
{
	Scene::~Scene()
	{
		for (Actor* actor : m_Actors)
			delete actor;
	}

	void Scene::Add(Actor* _actor)
	{
		m_Actors.push_back(_actor);
	}

	void Scene::Update()
	{
	}


}
