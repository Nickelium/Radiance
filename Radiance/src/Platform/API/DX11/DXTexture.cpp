#include "pch.h"
#include "DXTexture.h"

namespace Radiance
{

	int DXTexture2D::GetWidth() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	int DXTexture2D::GetHeight() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXTexture2D::Resize(int _width, int _height)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXTexture2D::SetData(void* _data, size_t _bytes)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXTexture2D::Bind(int _slot /*= 0*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXTexture2D::UnBind()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	Handle DXTexture2D::GetHandle() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	ID3D11Texture2D* DXTexture2D::GetInternalTexture() const
	{
		return m_D3D11Texture2D;
	}

}