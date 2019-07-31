#include "pch.h"
#include "RenderAPI.h"

#include "Radiance/Defines.h"

namespace Radiance
{
	#ifdef OPENGL_API
	RenderAPI::API RenderAPI::s_API(RenderAPI::API::Type::OPENGL);
	#endif
	#ifdef D3D11_API
	RenderAPI::API RenderAPI::s_API(RenderAPI::API::Type::D3D11);
	#endif
}