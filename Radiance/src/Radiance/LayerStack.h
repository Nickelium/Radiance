#pragma once

#include <vector>

//Can't forward declare because is template parameter
#include "Layer.h"

namespace Radiance
{
	class LayerStack
	{
	public:
		using LayerIt = std::vector<Layer*>::iterator;
		using LayerCIt = std::vector<Layer*>::const_iterator;
		
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* _layer);
		void PopLayer(Layer* _layer);
		void PushOverlay(Layer* _overlay);
		void PopOverlay(Layer* _overlay);

		inline LayerIt begin() { return m_Layers.begin(); }
		inline LayerIt end() { return m_Layers.end(); }
		inline LayerCIt cbegin() { return m_Layers.cbegin(); }
		inline LayerCIt cend() { return m_Layers.cend(); }

	private:
		std::vector<Layer*> m_Layers;
		LayerCIt m_LayerInsert;
	};
}
