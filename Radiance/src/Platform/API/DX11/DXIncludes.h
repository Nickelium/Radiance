#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>


//inline void SafeRelease(IUnknown* pResource)
//{
//	if (pResource != nullptr && *pResource != NULL)
//	{
//
//	}
//}

template<typename T>
inline void SafeRelease(T& ptr)
{
	if (ptr != NULL)
	{
		auto p = ptr->Release(); // OKAY only call release when it has a reference count, addref will add reference count, and on creation
		p;
		ptr = NULL;
	}
}
