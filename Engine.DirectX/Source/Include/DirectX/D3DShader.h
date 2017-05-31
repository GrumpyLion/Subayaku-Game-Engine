#pragma once

#include <d3d11.h>
#include <D3Dcompiler.h>

#include "Graphics\Interface\IShader.h"

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DShader : public IShader
		{
		private:
			//We need to declare all types and only use one of them ..
			ID3D11VertexShader *m_VertexShader = nullptr;
			ID3D11PixelShader *m_PixelShader = nullptr;
			ID3D10Blob *m_ShaderBuffer = nullptr;

			D3DRenderer *m_Renderer = nullptr;

			SShaderDesc m_Desc{};

		public:
			~D3DShader();
			bool Initialize(SShaderDesc &a_Desc, IRenderer *a_Renderer) override;
			void Bind();
			ID3D10Blob *GetShaderBuffer();
		};
	}
}