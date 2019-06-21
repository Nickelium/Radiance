#pragma once

#include "Radiance/Input.h"

namespace Radiance
{
	class Application;
	class WindowsInput : public Input 
	{
	public:
		WindowsInput(Application& _application);
	protected:
		virtual bool IsKeyPressedImpl(int _keyCode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;

		Application& m_Application;

	};
}
