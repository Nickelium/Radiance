#pragma once

#include "Radiance/Renderer/API/DeviceFactory.h"

struct IDXGIFactory2; 
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;

namespace Radiance
{
	class DXFactory : public DeviceFactory
	{
	public:
		DXFactory();

		virtual RenderDevice* CreateRenderDevice() override;
		virtual DeviceContext* CreateDeviceContext() override;
		virtual PlatformContext* CreatePlatformContext(Window* _window) override;

		inline IDXGIFactory2* GetInternalFactory() const { return m_InternalFactory; }
		inline ID3D11Device* GetInternalRenderDevice() const { return m_D3D11RenderDevice; }
		inline ID3D11DeviceContext* GetInternalDeviceContext() const { return m_D3D11DeviceContext; }
	private:
		void ConstructInternals();

		IDXGIFactory2* m_InternalFactory = nullptr;

		ID3D11Device* m_D3D11RenderDevice = nullptr;
		ID3D11DeviceContext* m_D3D11DeviceContext = nullptr;
		IDXGISwapChain* m_DXGISwapChain = nullptr;
	};
}