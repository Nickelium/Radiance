#include "pch.h"
#include "DXPlatformContext.h"

#include "Radiance/Core/Window.h"

#include "DXIncludes.h"

struct GLFWwindow;
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Radiance
{

	DXPlatformContext::DXPlatformContext(DXFactory* _factory, Window* _window)
		: m_Factory(_factory), m_Window(_window), 
		// Hard depedency
		m_WindowHandle(glfwGetWin32Window(reinterpret_cast<GLFWwindow*>(_window->GetNativeWindow())))
	{
	}

	void DXPlatformContext::Init()
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		memset(&swapChainDesc, 0, sizeof(swapChainDesc));
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Width = m_Window->GetWidth();
		swapChainDesc.Height = m_Window->GetHeight();
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		auto result = m_Factory->GetInternalFactory()->CreateSwapChainForHwnd(
			m_Factory->GetInternalRenderDevice(), m_WindowHandle, &swapChainDesc, nullptr, nullptr, &m_SwapChain);
		RAD_ASSERT(result == S_OK, "Failed to create swapchain");
	}

	void DXPlatformContext::SwapBuffers()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}