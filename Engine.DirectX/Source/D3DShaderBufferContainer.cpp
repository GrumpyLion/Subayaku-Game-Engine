#include "DirectX\D3DShaderBufferContainer.h"
#include "DirectX\D3DRenderer.h"

namespace Graphics
{
	namespace DirectX
	{
		void D3DShaderBufferContainer::Initialize(D3DRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			SShaderBufferDesc desc{};
			m_ConstantGlobalBuffer = std::make_unique<D3DShaderBuffer>();

			desc.BufferIndex = EBufferIndex::GlobalDynamicBuffer;
			desc.BufferSize = sizeof(DynamicBuffer);
			m_DynamicGlobalBuffer = std::make_unique<D3DShaderBuffer>();
			m_DynamicGlobalBuffer->Initialize(desc, a_Renderer);
		}

		void D3DShaderBufferContainer::Bind()
		{
			//Bind constant buffer
			DynamicBuffer dynamicData{};

			if (m_Renderer->GetCamera() != nullptr)
			{
				Matrix4f temp = m_Renderer->GetCamera()->ToProjectionMatrixLH;
				temp.Transpose();
				dynamicData.Projection = temp;

				temp = m_Renderer->GetCamera()->ToViewMatrixLH;
				temp.Transpose();
				dynamicData.View = temp;

				dynamicData.CameraPosition = m_Renderer->GetCamera()->Parent->Transform->Position;
			}

			dynamicData.TimeSinceStart = (float)m_Renderer->GetEngine()->TimeSinceStart;

			m_DynamicGlobalBuffer->Bind(&dynamicData);
		}
	}
}