#include "Radiance/Renderer/API/DeviceFactory.h"

namespace Radiance
{
	class RenderDevice;
	class DeviceContext;
	class PlatformContext;

	class GLFactory : public DeviceFactory
	{
	public:
		virtual RenderDevice* CreateRenderDevice() override;
		virtual DeviceContext* CreateDeviceContext() override;
		virtual PlatformContext* CreatePlatformContext(Window* _window) override;
	};
}