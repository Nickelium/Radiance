#pragma once

// Intended for client application usage
// Include once

#include "Radiance/Base.h"
#include "Radiance/Core/Logger.h"
#include "Radiance/Core/Time.h"

#include "Radiance/Core/Application.h"

#include "Radiance/Core/Layer.h"
#include "Radiance/ImGui/ImGuiLayer.h"

#include "Radiance/ImGui/ImGuiUtilities.h"

#include "Radiance/Input.h"
#include "Radiance/KeyCodes.h"
#include "Radiance/MouseButtonCodes.h"

#include "Radiance/Renderer/API/Shader.h"
#include "Radiance/Renderer/API/Buffer.h"
#include "Radiance/Renderer/API/VertexArray.h"
#include "Radiance/Renderer/API/Buffer.h"
#include "Radiance/Renderer/API/Texture.h"
#include "Radiance/Renderer/API/BufferView.h"
#include "Radiance/Renderer/API/FrameBuffer.h"

#include "Radiance/Renderer/Renderer.h"
#include "Radiance/Renderer/MeshRender.h"
#include "Radiance/Renderer/Camera/Orthographic.h"
#include "Radiance/Renderer/Camera/Perspective.h"
#include "Radiance/Renderer/Camera/OrthographicController.h"
#include "Radiance/Renderer/Camera/PerspectiveController.h"

#include "Radiance/Components/Actor.h"
#include "Radiance/Components/Component.h"
#include "Radiance/Components/TransformComponent.h"
#include "Radiance/Components/MeshComponent.h"

#include "Radiance/Prefab/Prefab.h"

#include "Radiance/Resources/ResourceLibrary.h"

#include "Radiance/Renderer/API/RenderDevice.h"
#include "Radiance/Renderer/API/DeviceContext.h"
#include "Radiance/Renderer/API/PlatformContext.h"

#include "Radiance/Renderer/API/DeviceFactory.h"

// Vendor
#include <glm/glm.hpp>
#include <imgui.h>

