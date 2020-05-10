#include "pch.h"
#include "DXFactory.h"

#include "DXRenderDevice.h"
#include "DXDeviceContext.h"
#include "DXPlatformContext.h"

#include "Radiance/Core/Window.h"

#include "DXIncludes.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

namespace Radiance
{
	DXFactory::DXFactory()
	{
		ConstructInternals();
	}

	void DXFactory::ConstructInternals()
	{
		//Alternative D3D11CreateDeviceAndSwapChain with default adapters
		auto result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&m_InternalFactory));
		RAD_CORE_ASSERT(result == S_OK, "Failed to create DXGIFactory");

		unsigned int deviceFlag = 0;
		#if RAD_DEBUG
		deviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
		#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};
		RAD_CORE_ASSERT(featureLevels, "Feature levels must be non null");
		constexpr unsigned char size = sizeof(featureLevels) / sizeof(featureLevels[0]);
		constexpr bool cond = size > 0;
		RAD_CORE_ASSERT(cond, "Feature levels must at least containt one element");
		D3D_FEATURE_LEVEL supportedFeatureLevel;
		result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlag, featureLevels, size, D3D11_SDK_VERSION, &m_D3D11RenderDevice, &supportedFeatureLevel, &m_D3D11DeviceContext);
		RAD_CORE_ASSERT(result == S_OK, "Failed to create Device and DeviceContext");
	}

	RenderDevice* DXFactory::CreateRenderDevice() 
	{
		return new DXRenderDevice(m_D3D11RenderDevice);
	}

	DeviceContext* DXFactory::CreateDeviceContext() 
	{
		return new DXDeviceContext(m_D3D11DeviceContext);
	}

	PlatformContext* DXFactory::CreatePlatformContext(Window* _window)
	{
		return new DXPlatformContext(this, _window);
	}
}