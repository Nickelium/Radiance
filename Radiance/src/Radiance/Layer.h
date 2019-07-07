#pragma once

#include "Events/Event.h"
#include "Renderer/Scene.h"

namespace Radiance
{
	class Application;
	/**
	 * Should be subclassed
	 */
	class Layer
	{
	public:
		Layer(Application* _application, Scene* _scene = nullptr);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void Update() {}
		virtual void Render() {}
		virtual void RenderGUI() {}

		virtual void OnEvent(Event& /*_event*/) {}

	protected:
		Application* m_Application;
		Scene* m_Scene;
	};
}