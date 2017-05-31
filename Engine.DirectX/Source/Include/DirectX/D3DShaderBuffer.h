#pragma once

#include "Graphics\Interface\IShaderBuffer.h"
#include <d3d11.h>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DShaderBuffer : public IShaderBuffer
		{
		private:
			SShaderBufferDesc m_Desc{};
			ID3D11Buffer *m_Buffer = nullptr;
			D3DRenderer *m_Renderer = nullptr;

		public:
			~D3DShaderBuffer();

			bool Initialize(SShaderBufferDesc &a_Desc, IRenderer *a_Renderer) override;
			void Bind(void* a_BufferData);
		};
	}
}