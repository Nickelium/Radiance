#include "pch.h"
#include "DXPlatformContext.h"

#include "Radiance/Core/Window.h"

#include "DXIncludes.h"

struct GLFWwindow;
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "DXSwapChain.h"
#include "Radiance/Renderer/API/Texture.h"
#include "DXTexture.h"

namespace Radiance
{

	DXPlatformContext::DXPlatformContext(DXFactory* _factory, Window* _window)
		: m_Factory(_factory), m_Window(_window), 
		// TODO remove hard dependency
		m_WindowHandle(glfwGetWin32Window(reinterpret_cast<GLFWwindow*>(_window->GetNativeWindow())))
	{
		m_SwapChain = new DXSwapChain(this);
		Init();
	}

	void DXPlatformContext::Init()
	{
	}

	void DXPlatformContext::SwapBuffers()
	{
		m_SwapChain->SwapBuffers();
	}

	Texture2D* DXPlatformContext::GetBackBufferTexture()
	{
		return m_SwapChain->GetBackBufferTexture();
	}

}