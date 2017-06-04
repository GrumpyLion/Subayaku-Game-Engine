#include "DirectX\D3DShaderBuffer.h"
#include "DirectX\D3DHelper.h"
#include "DirectX\D3DRenderer.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DShaderBuffer::~D3DShaderBuffer()
		{
			SafeRelease(m_Buffer);
		}

		bool D3DShaderBuffer::Initialize(SShaderBufferDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			D3D11_BUFFER_DESC matrixBufferDesc{};
			m_Desc = a_Desc;

			matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			matrixBufferDesc.ByteWidth = a_Desc.BufferSize;
			matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			matrixBufferDesc.MiscFlags = 0;
			matrixBufferDesc.StructureByteStride = 0;

			if (Failed(m_Renderer->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer)))
				return false;
			
			return true;
		}


		void D3DShaderBuffer::Bind(void* a_BufferData)
		{
			D3D11_MAPPED_SUBRESOURCE mappedRessource{};
			void *dataPtr = nullptr;

			if (Failed(m_Renderer->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRessource)))
				return;

			dataPtr = mappedRessource.pData;

			memcpy(dataPtr, a_BufferData, m_Desc.BufferSize);

			m_Renderer->GetDeviceContext()->Unmap(m_Buffer, 0);

			m_Renderer->GetDeviceContext()->VSSetConstantBuffers(m_Desc.BufferIndex, 1, &m_Buffer);
			m_Renderer->GetDeviceContext()->PSSetConstantBuffers(m_Desc.BufferIndex, 1, &m_Buffer);
		}
	}
}