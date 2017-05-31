#include "D3DTexture.h"
#include "D3DHelper.h"
#include "D3DRenderer.h"

#include "Core\Engine.h"

namespace Graphics
{
	namespace DirectX
	{

		D3DTexture::~D3DTexture()
		{
			SafeRelease(m_Texure);
			SafeRelease(m_SampleState);
		}

		bool D3DTexture::Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			D3D11_SAMPLER_DESC samplerDesc{};

			RegisterIndex = a_Desc.RegisterIndex;

			D3D11_TEXTURE2D_DESC td{};
			td.ArraySize = 1;
			td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			td.Usage = D3D11_USAGE_DYNAMIC;
			td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			td.Format = ETextureFormatToDX(a_Desc.Format);
			td.Height = a_Desc.Height;
			td.Width = a_Desc.Width;
			td.MipLevels = 1;
			td.MiscFlags = 0;
			td.SampleDesc.Count = 1;
			td.SampleDesc.Quality = 0;

			D3D11_SUBRESOURCE_DATA srd{};
			srd.pSysMem = a_Desc.PixelData.data();
			srd.SysMemPitch = a_Desc.Width * 4;

			ID3D11Texture2D *texture = nullptr;
			if (Failed(m_Renderer->GetDevice()->CreateTexture2D(&td, &srd, &texture)))
				return false;

			if (Failed(m_Renderer->GetDevice()->CreateShaderResourceView(texture, nullptr, &m_Texure)))
				return false;

			SafeRelease(texture);

			// Create a texture sampler state description.
			samplerDesc.Filter = ETextureFilterToDX(a_Desc.Filter);
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

			if (Failed(m_Renderer->GetDevice()->CreateSamplerState(&samplerDesc, &m_SampleState)))
				return false;

			return true;
		}

		void D3DTexture::Bind()
		{
			m_Renderer->GetDeviceContext()->VSSetSamplers(0, 1, &m_SampleState);
			m_Renderer->GetDeviceContext()->PSSetSamplers(0, 1, &m_SampleState);

			m_Renderer->GetDeviceContext()->VSSetShaderResources(RegisterIndex, 1, &m_Texure);
			m_Renderer->GetDeviceContext()->PSSetShaderResources(RegisterIndex, 1, &m_Texure);
		}

		void D3DTexture::Unbind()
		{

		}
	}
}