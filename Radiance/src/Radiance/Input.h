#pragma once

namespace Radiance
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int _keyCode) { return s_Instance->IsKeyPressedImpl(_keyCode); }
		inline static bool IsMouseButtonPressed(int _button) { return s_Instance->IsKeyPressedImpl(_button); }
		inline static float GetMouseX() { return GetMousePosition().first; }
		inline static float GetMouseY() { return GetMousePosition().second; }
		inline static std::pair<float, float> GetMousePosition() { s_Instance->GetMousePositionImpl(); }

		static std::unique_ptr<Input> s_Instance;
	protected:
		virtual bool IsKeyPressedImpl(int _keyCode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	private: 
	};
}
