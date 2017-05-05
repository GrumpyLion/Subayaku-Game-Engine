#pragma once

#include "Graphics\Interface\IRenderer.h"

#include <DirectX\Include\d3d11.h>
#include <DirectX\Include\D3DX11async.h>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer : public IRenderer
		{
		private:
			SRendererDesc m_Desc{};

			ID3D11Device* m_Device;
			ID3D11DeviceContext* m_DeviceContext;
			IDXGISwapChain* m_SwapChain;
			ID3D11RenderTargetView* m_RenderTargetView;
			ID3D11DepthStencilState* m_DepthStencilState;
			ID3D11Texture2D* m_TextureDepthBuffer;
			ID3D11BlendState* m_BlendState;

		public:
			bool Initialize(SRendererDesc &a_Desc) override;
			void Render() override;
			void Shutdown() override;
			void AddRenderable(Scene::CMeshRenderer *a_MeshRenderer) override;
			void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) override;
			void SetCamera(Scene::CCamera *a_Camera) override;
			Scene::CCamera *GetCamera() override;
		};
	}
}