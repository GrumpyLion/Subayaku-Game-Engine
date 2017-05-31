#include "D3DShader.h"
#include "D3DRenderer.h"

#include "Math\Math.h"
#include "D3DHelper.h"
#include "Graphics\Cache\SShaderDesc.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DShader::~D3DShader()
		{
			SafeRelease(m_PixelShader);
			SafeRelease(m_VertexShader);
			SafeRelease(m_ShaderBuffer);
		}

		bool D3DShader::Initialize(SShaderDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			m_Desc = a_Desc;

			ID3D10Blob *errorMessage = nullptr;		

			switch (a_Desc.Type)
			{
				case EShaderType::VertexShader:
				{
					if (FAILED(D3DCompile(a_Desc.HLSLCode.data(), a_Desc.HLSLCode.size(), a_Desc.HLSLCode.c_str(), nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &m_ShaderBuffer, &errorMessage)))
					{
						if (errorMessage != nullptr)
						{
							char* ptr = (char*)errorMessage->GetBufferPointer();
							OutputDebugStringA(ptr);
						}
						return false;
					}

					if (Failed(m_Renderer->GetDevice()->CreateVertexShader(m_ShaderBuffer->GetBufferPointer(), m_ShaderBuffer->GetBufferSize(), nullptr, &m_VertexShader)))
						return false;

					break;
				}

				case EShaderType::FragmentShader:
				{
					if (FAILED(D3DCompile(a_Desc.HLSLCode.data(), a_Desc.HLSLCode.size(), a_Desc.HLSLCode.c_str(), nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &m_ShaderBuffer, &errorMessage)))
					{
						if (errorMessage != nullptr)
						{
							char* ptr = (char*)errorMessage->GetBufferPointer();
							OutputDebugStringA(ptr);
						}
						return false;
					}

					if (Failed(m_Renderer->GetDevice()->CreatePixelShader(m_ShaderBuffer->GetBufferPointer(), m_ShaderBuffer->GetBufferSize(), nullptr, &m_PixelShader)))
						return false;
					
					break;
				}
			}

			SafeRelease(errorMessage);
			return true;
		}

		void D3DShader::Bind()
		{
			switch (m_Desc.Type)
			{
			case EShaderType::VertexShader:
				m_Renderer->GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, NULL);
				break;
			
			case EShaderType::FragmentShader:
				m_Renderer->GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, NULL);
				break;
			}
		}

		ID3D10Blob *D3DShader::GetShaderBuffer()
		{		return m_ShaderBuffer;		}
	}
}