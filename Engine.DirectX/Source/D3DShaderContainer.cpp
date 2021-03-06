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
			
			D3D11_INPUT_ELEMENT_DESC polygonLayout[9];
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


			// Matrix in buffer for instanced rendering ..
			// Divided in float4's

			polygonLayout[5].SemanticName = "WMATRIX";
			polygonLayout[5].SemanticIndex = 0;
			polygonLayout[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			polygonLayout[5].InputSlot = 5;
			polygonLayout[5].AlignedByteOffset = 0;
			polygonLayout[5].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			polygonLayout[5].InstanceDataStepRate = 1;

			polygonLayout[6].SemanticName = "WMATRIX";
			polygonLayout[6].SemanticIndex = 1;
			polygonLayout[6].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			polygonLayout[6].InputSlot = 5;
			polygonLayout[6].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[6].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			polygonLayout[6].InstanceDataStepRate = 1;

			polygonLayout[7].SemanticName = "WMATRIX";
			polygonLayout[7].SemanticIndex = 2;
			polygonLayout[7].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			polygonLayout[7].InputSlot = 5;
			polygonLayout[7].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[7].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			polygonLayout[7].InstanceDataStepRate = 1;

			polygonLayout[8].SemanticName = "WMATRIX";
			polygonLayout[8].SemanticIndex = 3;
			polygonLayout[8].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			polygonLayout[8].InputSlot = 5;
			polygonLayout[8].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[8].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			polygonLayout[8].InstanceDataStepRate = 1;

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

			if(m_VertexShader != nullptr)
				m_VertexShader->Bind();
			
			if (m_FragmentShader != nullptr)
				m_FragmentShader->Bind();
		}

		void D3DShaderContainer::UnbindProgram() 
		{

		}

		bool D3DShaderContainer::GetError() 
		{
			return true;
		}

		bool D3DShaderContainer::SetInt(const char* a_UniformName, const int a_Value) { return false; }
		bool D3DShaderContainer::SetFloat(const char* a_UniformName, const float a_Value) { return false; }
		bool D3DShaderContainer::SetVector2f(const char* a_UniformName, const Vector2f &a_Vec) { return false; }
		bool D3DShaderContainer::SetVector3f(const char* a_UniformName, const Vector3f &a_Vec) { return false; }
		bool D3DShaderContainer::SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat) { return false; }
	}
}