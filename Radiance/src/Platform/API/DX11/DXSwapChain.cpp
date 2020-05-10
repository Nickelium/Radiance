#include "pch.h"
#include "DXSwapChain.h"

namespace Radiance
{
	DXSwapChain::DXSwapChain(IDXGISwapChain* _internalSwapChain)
		: m_InternalSwapChain(_internalSwapChain)
	{
	}
}