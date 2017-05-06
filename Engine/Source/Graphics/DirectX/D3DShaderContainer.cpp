#include "D3DShaderContainer.h"

#include "Utilities\Utilities.h"
#include "Core\Engine.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DShaderContainer::~D3DShaderContainer()
		{
			SafeRelease(m_Layout);
			SafeRelease(m_PixelShader);
			SafeRelease(m_VertexShader);
		}

		bool D3DShaderContainer::Initialize(Material *a_Material)
		{
			m_Renderer = dynamic_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			ID3D10Blob *errorMessage = nullptr;
			ID3D10Blob *vertexShaderBuffer = nullptr;
			ID3D10Blob *pixelShaderBuffer = nullptr;
			D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
			unsigned int numElements;

			std::ifstream fileStream(GetShaderLocation(Core::Engine::StaticClass()->GetContext(), a_Material->VertexShader));

			//Vertex Shader
			if (!fileStream)
			{
				LogErr("Error File not found %s\n", a_Material->VertexShader);
				return false;
			}

			std::string source((std::istreambuf_iterator<char>(fileStream)),
				std::istreambuf_iterator<char>());

			if (FAILED(D3DCompile(source.c_str(), source.length(), a_Material->VertexShader.c_str(), nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &vertexShaderBuffer, &errorMessage)))
			{
				if (errorMessage != nullptr)
				{
					char* ptr = (char*)errorMessage->GetBufferPointer();
					OutputDebugStringA(ptr);
				}
				return false;
			}

			fileStream = std::ifstream(GetShaderLocation(Core::Engine::StaticClass()->GetContext(), a_Material->FragmentShader));

			//Fragment Shader
			if (!fileStream)
			{
				LogErr("Error File not found %s\n", a_Material->FragmentShader);
				return false;
			}

			source = std::string((std::istreambuf_iterator<char>(fileStream)),
				std::istreambuf_iterator<char>());

			if (FAILED(D3DCompile(source.c_str(), source.length(), a_Material->FragmentShader.c_str(), nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &pixelShaderBuffer, &errorMessage)))
			{
				if (errorMessage != nullptr)
				{
					char* ptr = (char*)errorMessage->GetBufferPointer();
					OutputDebugStringA(ptr);
				}
				return false;
			}

			if (Failed(m_Renderer->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_VertexShader)))
				return false;

			if (Failed(m_Renderer->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_PixelShader)))
				return false;

			polygonLayout[0].SemanticName = "POSITION";
			polygonLayout[0].SemanticIndex = 0;
			polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[0].InputSlot = 0;
			polygonLayout[0].AlignedByteOffset = 0;
			polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[0].InstanceDataStepRate = 0;

			polygonLayout[1].SemanticName = "NORMAL";
			polygonLayout[1].SemanticIndex = 0;
			polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[1].InputSlot = 1;
			polygonLayout[1].AlignedByteOffset = 0;
			polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[1].InstanceDataStepRate = 0;

			polygonLayout[2].SemanticName = "TEXCOORD";
			polygonLayout[2].SemanticIndex = 0;
			polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
			polygonLayout[2].InputSlot = 2;
			polygonLayout[2].AlignedByteOffset = 0;
			polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[2].InstanceDataStepRate = 0;

			numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

			if (Failed(m_Renderer->GetDevice()->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_Layout)))
				return false;

			//Release the shader buffer 
			vertexShaderBuffer->Release();
			vertexShaderBuffer = nullptr;

			pixelShaderBuffer->Release();
			pixelShaderBuffer = nullptr;

			return true;
		}

		void D3DShaderContainer::BindProgram()
		{
			m_Renderer->GetDeviceContext()->IASetInputLayout(m_Layout);

			m_Renderer->GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			m_Renderer->GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
		}

		void D3DShaderContainer::UnbindProgram() 
		{

		}

		bool D3DShaderContainer::GetError() 
		{
			return true;
		}

		//Fuck
		bool D3DShaderContainer::SetInt(const char* a_UniformName, const int a_Value) { return false; }
		bool D3DShaderContainer::SetFloat(const char* a_UniformName, const float a_Value) { return false; }
		bool D3DShaderContainer::SetVector2f(const char* a_UniformName, const Vector2f &a_Vec) { return false; }
		bool D3DShaderContainer::SetVector3f(const char* a_UniformName, const Vector3f &a_Vec) { return false; }
		bool D3DShaderContainer::SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat) { return false; }
	}
}