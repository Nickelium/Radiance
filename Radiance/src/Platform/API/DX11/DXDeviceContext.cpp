#include "pch.h"
#include "DXDeviceContext.h"


namespace Radiance
{
	DXDeviceContext::DXDeviceContext(ID3D11DeviceContext* _internalDeviceContext)
		: m_InternalDeviceContext(_internalDeviceContext)
	{
	}

	void DXDeviceContext::SetClearColor(const glm::vec4& /*_color*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXDeviceContext::Clear()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXDeviceContext::EnableDepth(bool /*_enable*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXDeviceContext::EnableBlend(bool /*_enable*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXDeviceContext::SetViewport(int /*_x*/, int /*_y*/, int /*_width*/, int /*_height*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXDeviceContext::DrawIndexed(VertexArray* /*_vertexArray*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
}
