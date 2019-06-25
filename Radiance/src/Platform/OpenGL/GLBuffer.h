#pragma once

#include "Radiance/Renderer/Buffer.h"

namespace Radiance
{

	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* _vertices, uint32_t _nbBytes);
		virtual ~GLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline virtual void SetLayout(const BufferLayout& _layout) override { m_Layout = _layout; }
		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		ID m_ID;

		BufferLayout m_Layout;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint32_t* _indices, uint32_t _count);
		virtual ~GLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline virtual uint32_t GetCount() const override { return m_Count; }
	private:
		ID m_ID;

		uint32_t m_Count;
	};
}
