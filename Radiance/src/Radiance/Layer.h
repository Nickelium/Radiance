#pragma once

#include "Events/Event.h"

namespace Radiance
{
	/**
	 * Should be subclassed
	 */
	class Layer
	{
	public:
		Layer(const std::string& _name = "Layer");
		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};

		virtual void OnEvent(Event& /*_event*/) {};

		inline const std::string& GetName() { return m_Name; }
	protected:
		std::string m_Name;
	};
}