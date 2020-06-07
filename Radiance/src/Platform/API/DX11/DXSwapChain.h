#pragma once

struct IDXGISwapChain1;

namespace Radiance
{
	class DXTexture2D;
	class DXPlatformContext;
	class DXSwapChain
	{
	public:
		DXSwapChain(DXPlatformContext* _platformContext);
		~DXSwapChain();

		void SwapBuffers();
		DXTexture2D* GetBackBufferTexture() const { return m_BackBufferTexture; }

	private:
		void CreateInternals();

		DXPlatformContext* m_PlatformContext;

		IDXGISwapChain1* m_DXGISwapChain = nullptr;
		DXTexture2D* m_BackBufferTexture;
	};
}
