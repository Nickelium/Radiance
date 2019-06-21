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
		ImGuiLayer(Application& _application);
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& _event) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& _event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& _event);
		bool OnMouseMovedEvent(MouseMovedEvent& _event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& _event);
		bool OnKeyPressedEvent(KeyPressedEvent& _event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& _event);
		bool OnKeyTypedEvent(KeyTypedEvent& _event);
		bool OnWindowsResized(WindowResizeEvent& _event);
	private:
		Application& m_Application;
		float m_Time = 0.0f;

	};
}
