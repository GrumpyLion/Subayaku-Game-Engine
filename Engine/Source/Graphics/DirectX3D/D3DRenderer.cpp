#include "D3DRenderer.h"

#include "D3DHelper.h"
#include "Utilities\Utilities.h"

namespace Graphics
{
	namespace DirectX
	{
		bool D3DRenderer::Initialize(SRendererDesc &a_Desc)
		{
			m_Desc = a_Desc;

			DXGI_SWAP_CHAIN_DESC swapChainDesc{};
			
			swapChainDesc.BufferDesc.Width = a_Desc.Width;
			swapChainDesc.BufferDesc.Height = a_Desc.Height;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 1;

			swapChainDesc.OutputWindow = a_Desc.Handle;
			swapChainDesc.Windowed = true; // need to change this
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = 0;

			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;

			D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
			
			if (Failed(D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG,
				&featureLevel,
				sizeof(featureLevel) / sizeof(D3D_FEATURE_LEVEL),
				D3D11_SDK_VERSION,
				&swapChainDesc,
				&m_SwapChain,
				&m_Device,
				nullptr,
				&m_DeviceContext
			)))
				return false;

			ID3D11Texture2D *backBuffer = nullptr;

			if (Failed(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
				return false;

			if (Failed(m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView)))
				return false;

			//We don't need this anymore
			NSafeRelease(backBuffer);
			
			D3D11_VIEWPORT viewport{};
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			
			viewport.Width = (FLOAT)a_Desc.Width;
			viewport.Height = (FLOAT)a_Desc.Height;
			
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			m_DeviceContext->RSSetViewports(1, &viewport);

			m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

			return true;
		}
		
		void D3DRenderer::Render()
		{
			float color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
			m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);

			Failed(m_SwapChain->Present(1, 0));
		}

		void D3DRenderer::AddRenderable(Scene::CMeshRenderer *a_MeshRenderer)
		{
			//..
		}
		
		void D3DRenderer::RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer)
		{
			//..
		}

		void D3DRenderer::SetCamera(Scene::CCamera *a_Camera)
		{
			//..
		}

		Scene::CCamera *D3DRenderer::GetCamera()
		{
			return nullptr;
		}

		void D3DRenderer::Shutdown()
		{
			NSafeRelease(m_DeviceContext);
			NSafeRelease(m_Device);
			NSafeRelease(m_SwapChain);
			NSafeRelease(m_RenderTargetView);
			NSafeRelease(m_DepthStencilState);
			NSafeRelease(m_TextureDepthBuffer);
			NSafeRelease(m_BlendState);
		}
	}
}