#pragma once

#include "Radiance/Renderer/API/PlatformContext.h"

#include "DXFactory.h"
#include <Windows.h>

struct IDXGISwapChain1;

namespace Radiance
{
	class Window;
	class Texture2D;
	class DXSwapChain;

	class DXPlatformContext : public PlatformContext
	{
	public:
		DXPlatformContext(DXFactory* _factory, Window* _Window);
		virtual void Init() override;
		virtual void SwapBuffers() override;

		virtual Texture2D* GetBackBufferTexture() override;
	public:
		DXFactory* GetFactory()const { return m_Factory; }
		Window* GetWindow()const { return m_Window; }
		HWND GetWindowHandle() const { return m_WindowHandle; }
	private:
		DXFactory* m_Factory = nullptr;
		Window* m_Window = nullptr;

		HWND m_WindowHandle = nullptr;

		DXSwapChain* m_SwapChain = nullptr;
	};
}
