#pragma once

namespace Radiance
{
	class RenderDevice;
	class DeviceContext;
	class PlatformContext;
	class Window;

	// Global Variable
	enum class RenderAPI
	{
		OPENGL = 0,
		DX11,
		NONE
	};
	extern RenderAPI API;

	#ifndef RAD_DEBUG
	#define VALIDATE_API
	#else
	#define VALIDATE_API ValidateAPI(API)
	#endif

	inline void ValidateAPI(RenderAPI _API) { assert(_API != RenderAPI::NONE && "Invalid RenderAPI or not supported"); }

	class DeviceFactory : public Service
	{
	public:
		virtual RenderDevice* CreateRenderDevice() = 0;
		virtual DeviceContext* CreateDeviceContext() = 0;
		virtual PlatformContext* CreatePlatformContext(Window* _window) = 0;

		static DeviceFactory* Create();

		SERVICE_CLASS(DeviceFactory)
	private:
	};
}