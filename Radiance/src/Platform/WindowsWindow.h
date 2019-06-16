#pragma once

#include "Radiance/Window.h"
//#include "Radiance/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace Radiance
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowDesc& _desc);
		virtual ~WindowsWindow();

		virtual void Update() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& _callback) override { m_Data.EventCallback = _callback; }
		void SetVSync(bool _enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowDesc& _desc);
		virtual void Destroy();
	private:
		GLFWwindow* m_Window;
		//GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}