#include "pch.h"
#include "DXSwapChain.h"

#include "DXIncludes.h"

#include "DXRenderDevice.h"
#include "DXPlatformContext.h"
#include "Radiance/Core/Window.h"
#include "DXTexture.h"

namespace Radiance
{
	DXSwapChain::DXSwapChain(DXPlatformContext* _platformContext)
		: m_PlatformContext(_platformContext)
	{
		CreateInternals();
	}

	DXSwapChain::~DXSwapChain()
	{
		delete m_BackBufferTexture;
		m_DXGISwapChain->Release();
	}

	void DXSwapChain::SwapBuffers()
	{
		m_DXGISwapChain->Present(m_PlatformContext->GetWindow()->IsVSync() ? 1 : 0, 0);
	}

	void DXSwapChain::CreateInternals()
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		memset(&swapChainDesc, 0, sizeof(swapChainDesc));
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Width = m_PlatformContext->GetWindow()->GetWidth();
		swapChainDesc.Height = m_PlatformContext->GetWindow()->GetHeight();
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		auto result = m_PlatformContext->GetFactory()->GetDXGIFactory()->CreateSwapChainForHwnd(
			GetDXRenderDevice()->GetD3D11Device(), m_PlatformContext->GetWindowHandle(), &swapChainDesc, nullptr, nullptr, &m_DXGISwapChain);
		RAD_ASSERT(result == S_OK, "Failed to create swapchain");

		ID3D11Texture2D* backBufferTexture;
		result = m_DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		RAD_ASSERT(result == S_OK, "Failed to get backbuffer");
		DXRenderDevice* renderDevice = GetDXRenderDevice();
		m_BackBufferTexture = renderDevice->CreateInternalTexture2D(backBufferTexture);
	}
}