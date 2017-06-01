#pragma once

#include "Graphics\Interfaces\ITexture.h"

#include <d3d11.h>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DTexture : public ITexture
		{
		private:
			ID3D11ShaderResourceView *m_Texure = nullptr;
			ID3D11SamplerState* m_SampleState = nullptr;

			D3DRenderer *m_Renderer = nullptr;
			int RegisterIndex = 0;

		public:
			~D3DTexture();
			bool Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer) final;

			void Bind();
			void Unbind();
		};
	}
}