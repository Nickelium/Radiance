#include "pch.h"
#include "Buffer.h"

#include "Platform/OpenGL/GLBuffer.h"
#include "Radiance/Renderer/Renderer.h"

namespace Radiance
{
	uint32_t DataTypeInfo::GetNbBytes() const
	{
		switch (type)
		{
		case Radiance::DataType::Float:	 return 4 * 1;
		case Radiance::DataType::Float2: return 4 * 2;
		case Radiance::DataType::Float3: return 4 * 3;
		case Radiance::DataType::Float4: return 4 * 4;
		case Radiance::DataType::Int:	 return 4 * 1;
		case Radiance::DataType::Int2:	 return 4 * 2;
		case Radiance::DataType::Int3:	 return 4 * 3;
		case Radiance::DataType::Int4:	 return 4 * 4;
		case Radiance::DataType::Mat3:	 return 4 * 9;
		case Radiance::DataType::Mat4:	 return 4 * 16;
		case Radiance::DataType::Bool:	 return 1;
		}
		RAD_CORE_ASSERT(false, "Invalid DataType");
		return 0u;
	}

	uint32_t DataTypeInfo::GetComponentCount() const
	{
		switch (type)
		{
		case Radiance::DataType::Float:	 return 1;
		case Radiance::DataType::Float2: return 2;
		case Radiance::DataType::Float3: return 3;
		case Radiance::DataType::Float4: return 4;
		case Radiance::DataType::Int:	 return 1;
		case Radiance::DataType::Int2:	 return 2;
		case Radiance::DataType::Int3:	 return 3;
		case Radiance::DataType::Int4:	 return 4;
		case Radiance::DataType::Mat3:	 return 9;
		case Radiance::DataType::Mat4:	 return 16;
		case Radiance::DataType::Bool:	 return 1;
		}
		RAD_CORE_ASSERT(false, "Invalid DataType");
		return 0u;
	}

}