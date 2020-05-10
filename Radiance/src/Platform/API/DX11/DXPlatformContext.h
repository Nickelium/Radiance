#pragma once

#include "Radiance/Renderer/API/PlatformContext.h"

#include "DXFactory.h"
#include <Windows.h>

struct IDXGISwapChain1;

namespace Radiance
{
	class Window;
	class Texture2D;

	class DXPlatformContext : public PlatformContext
	{
	public:
		DXPlatformContext(DXFactory* _factory, Window* _Window);
		virtual void Init() override;
		virtual void SwapBuffers() override;

		Texture2D* GetBackBuffer() const;
	private:
		DXFactory* m_Factory = nullptr;
		Window* m_Window = nullptr;

		HWND m_WindowHandle = nullptr;

		IDXGISwapChain1* m_SwapChain = nullptr;
	};
}
