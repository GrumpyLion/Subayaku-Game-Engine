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
		D3DShaderBufferContainer::~D3DShaderBufferContainer()
		{
			SafeDelete(m_ConstantGlobalBuffer);
			SafeDelete(m_DynamicGlobalBuffer);
		}

		void D3DShaderBufferContainer::Initialize()
		{
			m_Renderer = dynamic_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());
			SShaderBufferDesc desc{};
			m_ConstantGlobalBuffer = new D3DShaderBuffer();

			desc.BufferIndex = GlobalBufferPositions::DynamicGlobalBuffer;
			desc.BufferSize = sizeof(DynamicBuffer);
			m_DynamicGlobalBuffer = new D3DShaderBuffer();
			m_DynamicGlobalBuffer->Initialize(desc);

		}

		void D3DShaderBufferContainer::Bind()
		{
			//Bind constant buffer
			DynamicBuffer dynamicData{};

			Matrix4f temp = m_Renderer->GetCamera()->ToProjectionMatrixLH();
			temp.Transpose();
			dynamicData.Projection = temp;

			temp = m_Renderer->GetCamera()->ToViewMatrixLH();
			temp.Transpose();
			dynamicData.View = temp;

			dynamicData.TimeSinceStart = (float)Core::Engine::StaticClass()->GetTimeSinceStart();
			dynamicData.CameraPosition = Core::Engine::StaticClass()->GetRenderer()->GetCamera()->Parent->Transform->Position;

			m_DynamicGlobalBuffer->Bind(m_Renderer, &dynamicData);
		}
	}
}