#include "pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/GLRenderAPI.h"

namespace Radiance
{
	RenderAPI* RenderCommand::s_RenderAPI = new GLRenderAPI;

}