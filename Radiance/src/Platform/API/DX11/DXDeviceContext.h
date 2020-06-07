#pragma once

#include "Radiance/Renderer/API/DeviceContext.h"

struct ID3D11DeviceContext;

namespace Radiance
{
	class DXFrameBuffer;
	class DXDeviceContext : public DeviceContext
	{
	public:
		DXDeviceContext(ID3D11DeviceContext* _internalDeviceContext);
		virtual ~DXDeviceContext();

		virtual void SetClearColor(const glm::vec4& _color) override;
		virtual void Clear() override;
		virtual void EnableDepth(bool _enable) override;
		virtual void EnableBlend(bool _enable) override;
		virtual void SetViewport(int _x, int _y, int _width, int _height) override;
		virtual void DrawIndexed(VertexArray* _vertexArray) override;
		virtual void SetFrameBuffer(FrameBuffer* _frameBuffer) override;

	public:
		ID3D11DeviceContext* GetD3D11DeviceContext() const
		{
			return m_D3D11DeviceContext;
		}

	private:
		ID3D11DeviceContext* m_D3D11DeviceContext = nullptr;

		DXFrameBuffer* m_ActiveFrameBuffer = nullptr;
		glm::vec4 m_ClearColor;
		bool m_DepthEnabled = false;
	};

	DXDeviceContext* GetDXDeviceContext();
}