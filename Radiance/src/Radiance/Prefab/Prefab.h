#pragma once

#include "Radiance/Renderer/Mesh.h"
#include "Radiance/Renderer/API/Shader.h"
#include "Radiance/Renderer/API/RenderDevice.h"

namespace Radiance
{
	Mesh* CreateCube(RenderDevice* _renderDevice, Shader* _shader);
	Mesh* CreateTriangle(RenderDevice* _renderDevice, Shader* _shader);
}