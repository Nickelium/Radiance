#pragma once

#include "Radiance/Input.h"

namespace Radiance
{
	class Window;
	class WindowsInput : public Input 
	{
	public:
		WindowsInput(Window* _window);
	protected:
		virtual bool IsKeyPressedImpl(int _keyCode) override;
		virtual bool IsMousePressedImpl(int _button) override;
		virtual glm::vec2 GetMousePositionImpl() override;

		Window* m_Window;

	};
}
