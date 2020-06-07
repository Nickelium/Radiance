#pragma once

#include "Radiance/Renderer/API/DeviceFactory.h"

struct IDXGIFactory2; 
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
#ifdef RAD_DEBUG
	struct ID3D11Debug;
#endif

namespace Radiance
{
	class DXFactory : public DeviceFactory
	{
	public:
		DXFactory();
		virtual ~DXFactory();

		virtual RenderDevice* CreateRenderDevice() override;
		virtual DeviceContext* CreateDeviceContext() override;
		virtual PlatformContext* CreatePlatformContext(Window* _window) override;

		inline IDXGIFactory2* GetDXGIFactory() const { return m_DXGIFactory; }
		inline ID3D11Device* GetD3D11RenderDevice() const { return m_D3D11RenderDevice; }
		inline ID3D11DeviceContext* GetD3D11DeviceContext() const { return m_D3D11DeviceContext; }
	private:
		void ConstructInternals();

		void CreateD3D11Debug();

		IDXGIFactory2* m_DXGIFactory = nullptr;

		// Manages all device ressources
		ID3D11Device* m_D3D11RenderDevice = nullptr;
		ID3D11DeviceContext* m_D3D11DeviceContext = nullptr;

#ifdef RAD_DEBUG
		ID3D11Debug* m_D3D11Debug = nullptr;
#endif
	};
}