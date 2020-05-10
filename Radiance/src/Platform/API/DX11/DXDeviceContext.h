#pragma once

#include "Radiance/Renderer/API/DeviceContext.h"

struct ID3D11DeviceContext;

namespace Radiance
{
	class DXDeviceContext : public DeviceContext
	{
	public:
		DXDeviceContext(ID3D11DeviceContext* _internalDeviceContext);

		virtual void SetClearColor(const glm::vec4& _color) override;
		virtual void Clear() override;
		virtual void EnableDepth(bool _enable) override;
		virtual void EnableBlend(bool _enable) override;
		virtual void SetViewport(int _x, int _y, int _width, int _height) override;
		virtual void DrawIndexed(VertexArray* _vertexArray) override;
	private:
		ID3D11DeviceContext* m_InternalDeviceContext = nullptr;

	};
}