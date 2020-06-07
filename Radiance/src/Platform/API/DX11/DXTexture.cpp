#include "pch.h"
#include "DXTexture.h"

#include "DXIncludes.h"
#include "DXRenderDevice.h"

namespace Radiance
{
	DXTexture2D::DXTexture2D(ID3D11Texture2D* _internalTexture) : m_D3D11Texture2D(_internalTexture)
	{
		D3D11_TEXTURE2D_DESC textureDescriptor;
		m_D3D11Texture2D->GetDesc(&textureDescriptor);
		m_Width = textureDescriptor.Width;
		m_Height = textureDescriptor.Height;
		DXGI_FORMAT DXGIFormat = textureDescriptor.Format;
		switch (DXGIFormat)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			m_TextureFormat = TextureFormat::RGBA;
			break;
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
			m_TextureFormat = TextureFormat::DS;
			break;
		default:
			RAD_ASSERT(false, "Unsupported DXGIFormat: {0}", DXGIFormat);
		}

	}

	DXTexture2D::DXTexture2D(int _width, int _height, FormatUsage _formatUsage)
		: m_Width(_width), m_Height(_height), m_FormatUsage(_formatUsage)
	{
		D3D11_TEXTURE2D_DESC textureDescriptor;
		memset(&textureDescriptor, 0, sizeof(D3D11_TEXTURE2D_DESC));
		textureDescriptor.Width = m_Width;
		textureDescriptor.Height = m_Height;
		textureDescriptor.ArraySize = 1;
		textureDescriptor.CPUAccessFlags = 0; // No CPU access required.
		textureDescriptor.MipLevels = 1;
		textureDescriptor.SampleDesc.Count = 1;
		textureDescriptor.SampleDesc.Quality = 0;
		textureDescriptor.Usage = D3D11_USAGE_DEFAULT;

		switch (m_FormatUsage)
		{
		case FormatUsage::COLOR_BUFFER:
			textureDescriptor.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			textureDescriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		case FormatUsage::DEPTHSTENCIL_BUFFER:
			textureDescriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			textureDescriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			break;
		default:
			RAD_ASSERT(false, "Unsupported FormatUsage: {0}", static_cast<int>(m_FormatUsage));
		}

		ID3D11Device* d3d11Device = GetDXRenderDevice()->GetD3D11Device();
		HRESULT result = d3d11Device->CreateTexture2D(&textureDescriptor, nullptr, &m_D3D11Texture2D);
		RAD_ASSERT(result != S_OK, "Failed to create ID3D11Texture");
	}

	DXTexture2D::~DXTexture2D()
	{
		m_D3D11Texture2D->Release();
	}

	int DXTexture2D::GetWidth() const
	{
		return m_Width;
	}

	int DXTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void DXTexture2D::SetSize(int /*_width*/, int /*_height*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXTexture2D::SetData(void* /*_data*/, size_t /*_bytes*/)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void DXTexture2D::Bind(int /*_slot*/ /*= 0*/)
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

	ID3D11Texture2D* DXTexture2D::GetD3D11Texture() const
	{
		return m_D3D11Texture2D;
	}

}