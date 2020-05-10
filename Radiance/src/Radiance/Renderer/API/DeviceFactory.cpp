#include "pch.h"
#include "DeviceFactory.h"

#include "Platform/API/OpenGL/GLFactory.h"
#include "Platform/API/DX11/DXFactory.h"

namespace Radiance
{
	DeviceFactory* DeviceFactory::Create()
	{
		VALIDATE_API;
		switch (API)
		{
			case RenderAPI::OPENGL:
				API = RenderAPI::OPENGL;
				return new GLFactory;
			case RenderAPI::DX11:
				API = RenderAPI::DX11;
				return new DXFactory;
		}
		return nullptr;
	}
}