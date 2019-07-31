#include "pch.h"
#include "RenderDevice.h"

#include "Platform/OpenGL/GLRenderDevice.h"
#include "Radiance/Renderer/Renderer.h"

namespace Radiance
{
	RenderDevice* RenderDevice::Create()
	{
		switch (Renderer::GetAPI().type)
		{
		case RenderAPI::API::Type::OPENGL: return new GLRenderDevice;
		case RenderAPI::API::Type::D3D11: RAD_CORE_ASSERT(false, "RenderAPI:D3D11 not supported"); return nullptr;
		}

		RAD_CORE_ASSERT(false, "Invalid RenderAPI");
		return nullptr;
	}
}