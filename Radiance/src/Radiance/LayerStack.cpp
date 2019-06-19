#include "pch.h"
#include "LayerStack.h"

namespace Radiance
{
	LayerStack::LayerStack()
		: m_LayerInsert(m_Layers.cbegin())
	{

	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* _layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, _layer);
		//m_LayerInsert = m_Layers.insert(m_LayerInsert, _layer);
	}

	void LayerStack::PopLayer(Layer* _layer)
	{
		auto res = std::find(m_Layers.cbegin(), m_LayerInsert, _layer);
		if (res == m_Layers.cend())
			return;
		m_Layers.erase(res);
		--m_LayerInsert;
	}

	void LayerStack::PushOverlay(Layer* _overlay)
	{
		m_Layers.push_back(_overlay);
		m_Layers.emplace_back(_overlay);
	}

	void LayerStack::PopOverlay(Layer* _overlay)
	{
		auto res = std::find(m_LayerInsert, m_Layers.cend(), _overlay);
		if (res == m_Layers.cend())
			return;
		m_Layers.erase(res);
	}
}