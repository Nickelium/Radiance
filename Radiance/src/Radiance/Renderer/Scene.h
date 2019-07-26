#pragma once

#include "Radiance/Components/Actor.h"

namespace Radiance
{
	using Actors = std::vector<Actor*>;
	
	class Scene
	{
		Actors m_Actors;
	public:
		Scene() = default;
		~Scene();

		void Add(Actor* _actor);
		inline const Actors& GetActors() const { return m_Actors; }

		void Update();
	};
}
