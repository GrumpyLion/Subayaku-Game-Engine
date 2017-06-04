#include "DirectX\D3DShaderContainer.h"
#include "DirectX\D3DHelper.h"
#include "DirectX\D3DRenderer.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DShaderContainer::~D3DShaderContainer()
		{
			SafeRelease(m_Layout);
		}

		bool D3DShaderContainer::Initialize(SShaderContainerDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			m_VertexShader = static_cast<D3DShader*>(m_Renderer->GetCache()->LoadShader(a_Desc.Vertex));

			if (m_VertexShader == nullptr)
				return false;

			m_FragmentShader = static_cast<D3DShader*>(m_Renderer->GetCache()->LoadShader(a_Desc.Fragment));

			if (m_FragmentShader == nullptr)
				return false;
			
			D3D11_INPUT_ELEMENT_DESC polygonLayout[5];
			unsigned int numElements;

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

			polygonLayout[3].SemanticName = "TANGENT";
			polygonLayout[3].SemanticIndex = 0;
			polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[3].InputSlot = 3;
			polygonLayout[3].AlignedByteOffset = 0;
			polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[3].InstanceDataStepRate = 0;

			polygonLayout[4].SemanticName = "BITANGENT";
			polygonLayout[4].SemanticIndex = 0;
			polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[4].InputSlot = 4;
			polygonLayout[4].AlignedByteOffset = 0;
			polygonLayout[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[4].InstanceDataStepRate = 0;

			numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);			

			if (Failed(m_Renderer->GetDevice()->CreateInputLayout(
				polygonLayout, numElements, m_VertexShader->GetShaderBuffer()->GetBufferPointer(),
				m_VertexShader->GetShaderBuffer()->GetBufferSize(), &m_Layout)))

				return false;

			return true;
		}

		void D3DShaderContainer::BindProgram()
		{
			m_Renderer->GetDeviceContext()->IASetInputLayout(m_Layout);

			m_VertexShader->Bind();
			m_FragmentShader->Bind();
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