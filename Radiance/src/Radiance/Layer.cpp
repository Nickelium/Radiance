#include "pch.h"
#include "Layer.h"

namespace Radiance
{
	Layer::Layer(Application* _application, const std::string& _name /*= "Layer"*/)
		: m_Name(_name), m_Application(_application)
	{}
}