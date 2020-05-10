#include "pch.h"
#include "GLFactory.h"

#include "GLRenderDevice.h"
#include "GLDeviceContext.h"
#include "GLPlatformContext.h"

#include "Radiance/Core/Window.h"

namespace Radiance
{
	RenderDevice* GLFactory::CreateRenderDevice() 
	{
		return new GLRenderDevice;
	}

	DeviceContext* GLFactory::CreateDeviceContext() 
	{
		return new GLDeviceContext;
	}

	PlatformContext* GLFactory::CreatePlatformContext(Window* _window)
	{
		//TODO hard dependency
		GLFWwindow* glfwWindow = reinterpret_cast<GLFWwindow*>(_window->GetNativeWindow());
		return new GLPlatformContext(glfwWindow);
	}
}