#pragma once

#include "Graphics\Bases\BaseRenderer.h"

#include <d3d11.h>

#include "D3DEntity.h"
#include "D3DTexture.h"
#include "D3DMaterial.h"
#include "D3DMesh.h"
#include "D3DShader.h"
#include "D3DShaderBuffer.h"
#include "D3DShaderBufferContainer.h"

#include <memory>

namespace Graphics
{
	namespace DirectX
	{

		class D3DRenderer : public BaseRenderer<D3DEntity, D3DTexture, D3DMesh, D3DShader, D3DShaderBuffer>
		{
		private:
			SRendererDesc m_Desc{};
			std::unique_ptr<D3DShaderBufferContainer> m_BufferContainer = nullptr;

			ID3D11Device* m_Device = nullptr;
			ID3D11DeviceContext* m_DeviceContext = nullptr;
			IDXGISwapChain* m_SwapChain = nullptr;
			ID3D11RenderTargetView* m_RenderTargetView = nullptr;
			ID3D11DepthStencilState* m_DepthStencilState = nullptr;
			ID3D11Texture2D* m_TextureDepthBuffer = nullptr;
			ID3D11BlendState* m_BlendState = nullptr;
			ID3D11RasterizerState *m_RasterState = nullptr;
			ID3D11DepthStencilView *m_DepthStencilView = nullptr;
			ID3D11Texture2D *m_StencilBuffer = nullptr;
			
		public:

			__declspec(dllexport) ~D3DRenderer();

			__declspec(dllexport) bool Initialize(SRendererDesc &a_Desc) final;
			__declspec(dllexport) void Render() final;

			ID3D11Device* GetDevice();
			ID3D11DeviceContext* GetDeviceContext();
		};
	}
}