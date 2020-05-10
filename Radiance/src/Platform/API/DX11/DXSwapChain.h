#pragma once

struct IDXGISwapChain;

namespace Radiance
{
	class DXSwapChain
	{
	public:
		DXSwapChain(IDXGISwapChain* _internalSwapChain);
		void SwapBuffers();
	private:
		IDXGISwapChain* m_InternalSwapChain = nullptr;
	};
}
