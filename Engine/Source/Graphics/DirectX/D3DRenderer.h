#pragma once

#include "Graphics\Interface\IRenderer.h"

#include <d3d11.h>

#include "D3DEntity.h"
#include "D3DShaderBufferContainer.h"

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer : public IRenderer
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
			
			std::unordered_map<Scene::CMeshRenderer*, std::unique_ptr<D3DEntity>> m_Entities;

		public:
			Scene::CCamera *Camera = nullptr;
			~D3DRenderer();

			bool Initialize(SRendererDesc &a_Desc) override;
			void Render() override;
			void AddRenderable(Scene::CMeshRenderer *a_MeshRenderer) override;
			void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) override;
			void SetCamera(Scene::CCamera *a_Camera) override;
			Scene::CCamera *GetCamera() override;

			ID3D11Device* GetDevice();
			ID3D11DeviceContext* GetDeviceContext();
		};
	}
}