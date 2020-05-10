#pragma once

#include "Radiance/Renderer/Mesh.h"

namespace Radiance
{
	Mesh* CreateCube();
	Mesh* CreateTriangle();

	struct SphereDescriptor
	{
		float radius;
		uint8_t nbHorizontalSlices;
		uint8_t nbVerticalSlices;
	};
	Mesh* CreateSphere(SphereDescriptor _descriptor = {50.0f, 64, 64});
}