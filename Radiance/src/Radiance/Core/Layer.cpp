#include "pch.h"
#include "Layer.h"

namespace Radiance
{
	Layer::Layer(Application* _application, Scene* _scene)
		: m_Application(_application), m_Scene(_scene)
	{}

	Layer::~Layer()
	{
		delete m_Scene;
	}
}