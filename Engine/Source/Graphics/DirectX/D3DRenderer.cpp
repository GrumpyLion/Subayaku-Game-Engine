#include "D3DRenderer.h"

#include "D3DHelper.h"
#include "Utilities\Utilities.h"

#include "Core\Engine.h"
#include "Scene\Scene.h"

namespace Graphics
{
	namespace DirectX
	{
		bool D3DRenderer::Initialize(SRendererDesc &a_Desc)
		{
			m_Desc = a_Desc;

			DXGI_SWAP_CHAIN_DESC swapChainDesc{};
			D3D11_RASTERIZER_DESC rasterDesc{};
			D3D11_TEXTURE2D_DESC depthBufferDesc{};
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
			
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
			SafeRelease(backBuffer);
			
			D3D11_VIEWPORT viewport{};
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			
			viewport.Width = (FLOAT)a_Desc.Width;
			viewport.Height = (FLOAT)a_Desc.Height;
			
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			//Depth Buffer
			depthBufferDesc.Width = a_Desc.Width;
			depthBufferDesc.Height = a_Desc.Height;
			depthBufferDesc.MipLevels = 1;
			depthBufferDesc.ArraySize = 1;
			depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthBufferDesc.SampleDesc.Count = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags = 0;
			depthBufferDesc.MiscFlags = 0;

			if (Failed(m_Device->CreateTexture2D(&depthBufferDesc, NULL, &m_StencilBuffer)))
				return false;

			//Depth stencil
			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthStencilDesc.StencilEnable = true;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;

			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			if (Failed(m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState)))
				return false;

			m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1);

			//Raster desc
			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_BACK;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			if (Failed(m_Device->CreateRasterizerState(&rasterDesc, &m_RasterState)))
				return false;

			m_DeviceContext->RSSetState(m_RasterState);

			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;

			if (Failed(m_Device->CreateDepthStencilView(m_StencilBuffer, &depthStencilViewDesc, &m_DepthStencilView)))
				return false;

			m_DeviceContext->RSSetViewports(1, &viewport);

			m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

			//Getting the graphics card info
			IDXGIAdapter* adapter;	
			IDXGIFactory* factory;

			// Create a DirectX graphics interface factory.
			if (Failed(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
				return false;

			//Get the adapter
			if (Failed(factory->EnumAdapters(0, &adapter)))
				return false;

			DXGI_ADAPTER_DESC test;
			auto adapterDescription = adapter->GetDesc(&test);

			printf("Initializing DirectX Renderer..\n");
			wprintf(L"%s\n", test.Description);

			//Release it 
			SafeRelease(adapter);
			SafeRelease(factory);

			m_BufferContainer = std::make_unique<D3DShaderBufferContainer>();
			m_BufferContainer->Initialize(this);

			if (Core::Engine::StaticClass()->GetScene() != nullptr)
			{
				if (Core::Engine::StaticClass()->GetScene()->GetRenderables().size() > 0)
				{
					for (auto &temp : Core::Engine::StaticClass()->GetScene()->GetRenderables())
					{
						AddRenderable(temp.second);
					}
				}
			}

			if (Core::Engine::StaticClass()->GetScene() != nullptr)
			{
				SetCamera(Core::Engine::StaticClass()->GetScene()->GetCamera());
			}

			return true;
		}
		
		void D3DRenderer::Render()
		{
			float color[4] = { 0.2f, 0.4f, 0.6f, 1.0f };
			m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);
			m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

			m_BufferContainer->Bind();
			for (auto &temp : m_Entities)
			{
				temp.second->Render();
			}

			Failed(m_SwapChain->Present(1, 0));
		}

		void D3DRenderer::AddRenderable(Scene::CMeshRenderer *a_MeshRenderer)
		{
			if (CheckIfPointerIsInvalid(a_MeshRenderer))
				return;

			if (m_Entities.find(a_MeshRenderer) != m_Entities.end())
			{
				LogErr("CMeshrenderer is already added\n");
				return;
			}

			auto temp = std::make_unique<D3DEntity>();

			if (!temp->Initialize(a_MeshRenderer->GetMesh(), a_MeshRenderer->GetMaterial(), a_MeshRenderer->Parent))
			{
				LogErr("Error while trying to add a new Renderable\n");
				return;
			}

			m_Entities.insert({ a_MeshRenderer, std::move(temp) });
		}
		
		void D3DRenderer::RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer)
		{
			if (CheckIfPointerIsInvalid(a_MeshRenderer))
				return;

			if (m_Entities.find(a_MeshRenderer) == m_Entities.end())
			{
				LogErr("CMeshrenderer was not found\n");
				return;
			}
			else
			{
				m_Entities.erase(a_MeshRenderer);
			}
		}

		void D3DRenderer::SetCamera(Scene::CCamera *a_Camera)
		{
			Camera = a_Camera;
		}

		Scene::CCamera *D3DRenderer::GetCamera()
		{	return Camera;		}

		ID3D11Device* D3DRenderer::GetDevice()
		{	return m_Device;		}

		ID3D11DeviceContext* D3DRenderer::GetDeviceContext()
		{	return m_DeviceContext;		}

		D3DRenderer::~D3DRenderer()
		{
			m_Entities.clear();

			SafeRelease(m_DeviceContext);
			SafeRelease(m_Device);
			SafeRelease(m_SwapChain);
			SafeRelease(m_RenderTargetView);
			SafeRelease(m_DepthStencilState);
			SafeRelease(m_TextureDepthBuffer);
			SafeRelease(m_BlendState);
			SafeRelease(m_RasterState);
			SafeRelease(m_DepthStencilView);
			SafeRelease(m_StencilBuffer);
		}
	}
}