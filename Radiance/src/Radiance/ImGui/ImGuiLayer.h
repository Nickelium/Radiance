#pragma once

#include "Radiance/Layer.h"

#include "Radiance/Events/ApplicationEvent.h"
#include "Radiance/Events/MouseEvent.h"
#include "Radiance/Events/KeyEvent.h"

namespace Radiance
{
	class Application;
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Application* _application);
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;

	};
}
