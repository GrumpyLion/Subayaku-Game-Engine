#include "D3DShader.h"

#include "Math\Math.h"
#include "D3DHelper.h"
#include "Core\Engine.h"
#include "Utilities\Utilities.h"
#include "D3DRenderer.h"

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

		bool D3DShader::Initialize(SShaderDesc &a_Desc)
		{
			m_Desc = a_Desc;

			m_Renderer = static_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			ID3D10Blob *errorMessage = nullptr;		

			std::ifstream fileStream(GetShaderLocation(Core::Engine::StaticClass()->GetContext(), a_Desc.FilePath));

			//Vertex Shader
			if (!fileStream)
			{
				LogErr("File not found %s\n", a_Desc.FilePath);
				return false;
			}

			std::string source((std::istreambuf_iterator<char>(fileStream)),
				std::istreambuf_iterator<char>());

			switch (a_Desc.Type)
			{
				case EShaderType::VertexShader:
				{
					if (FAILED(D3DCompile(source.c_str(), source.length(), a_Desc.FilePath.c_str(), nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &m_ShaderBuffer, &errorMessage)))
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
					if (FAILED(D3DCompile(source.c_str(), source.length(), a_Desc.FilePath.c_str(), nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &m_ShaderBuffer, &errorMessage)))
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

			fileStream.close();
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