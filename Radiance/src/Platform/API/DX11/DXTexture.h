#pragma once

#include "Radiance/Renderer/API/Texture.h"

struct ID3D11Texture2D;

namespace Radiance
{
	struct Data
	{
		void* data = nullptr;
		size_t bytes = 0;
	};

	class DXTexture2D : public Texture2D
	{
	public:
		DXTexture2D(ID3D11Texture2D* _d3d11Texture2D);
		DXTexture2D(int _width, int _height, FormatUsage _formatUsage = FormatUsage::COLOR_BUFFER);
		virtual ~DXTexture2D();

		virtual int GetWidth() const override;
		virtual int GetHeight() const override;
		virtual void SetSize(int _width, int _height) override;
		virtual void SetData(void* _data, size_t _bytes) override;
		virtual void Bind(int _slot = 0) override;
		virtual void UnBind() override;
		virtual Handle GetHandle() const override;

		ID3D11Texture2D* GetD3D11Texture() const;
	private:
		Data m_Data;
		int m_Width, m_Height, m_BPP;
		TextureFormat m_TextureFormat;
		FormatUsage m_FormatUsage;

		ID3D11Texture2D* m_D3D11Texture2D = nullptr;
	};
}
