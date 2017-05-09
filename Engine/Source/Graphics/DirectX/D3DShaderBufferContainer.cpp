#include "D3DShaderBufferContainer.h"

#include "D3DRenderer.h"
#include "Utilities\Utilities.h"
#include "Core\Engine.h"
#include "Scene\GameObject\Components\CCamera.h"
#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	namespace DirectX
	{
		void D3DShaderBufferContainer::Initialize(D3DRenderer *a_Renderer)
		{
			m_Renderer = a_Renderer;
			SShaderBufferDesc desc{};
			m_ConstantGlobalBuffer = std::make_unique<D3DShaderBuffer>();

			desc.BufferIndex = EBufferIndex::GlobalDynamicBuffer;
			desc.BufferSize = sizeof(DynamicBuffer);
			m_DynamicGlobalBuffer = std::make_unique<D3DShaderBuffer>();
			m_DynamicGlobalBuffer->Initialize(desc);
		}

		void D3DShaderBufferContainer::Bind()
		{
			//Bind constant buffer
			DynamicBuffer dynamicData{};

			if (m_Renderer->GetCamera() != nullptr)
			{
				Matrix4f temp = m_Renderer->GetCamera()->ToProjectionMatrixLH();
				temp.Transpose();
				dynamicData.Projection = temp;

				temp = m_Renderer->GetCamera()->ToViewMatrixLH();
				temp.Transpose();
				dynamicData.View = temp;

				dynamicData.CameraPosition = Core::Engine::StaticClass()->GetRenderer()->GetCamera()->Parent->Transform->Position;
			}
			dynamicData.TimeSinceStart = (float)Core::Engine::StaticClass()->GetTimeSinceStart();

			m_DynamicGlobalBuffer->Bind(m_Renderer, &dynamicData);
		}
	}
}