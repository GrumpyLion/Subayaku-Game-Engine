#include "GLShaderBufferContainer.h"

#include "GLRenderer.h"

#include "Graphics\GlobalIndices.h"
#include "Utilities\Utilities.h"
#include "Core\Engine.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "Scene\GameObject\Components\CCamera.h"

namespace Graphics
{
	namespace OpenGL
	{		
		void GLShaderBufferContainer::Initialize(GLRenderer *a_Renderer)
		{
			m_Renderer = static_cast<GLRenderer*>(a_Renderer);

			SShaderBufferDesc desc{};

			m_ConstantGlobalBuffer = std::make_unique<GLShaderBuffer>();

			m_DynamicGlobalBuffer = std::make_unique<GLShaderBuffer>();

			desc = SShaderBufferDesc{};
			desc.BufferIndex = EBufferIndex::GlobalDynamicBuffer;
			desc.BufferSize = sizeof(DynamicBuffer);
			desc.IsDynamic = true;

			m_DynamicGlobalBuffer->Initialize(desc, m_Renderer);
		}

		void GLShaderBufferContainer::Bind()
		{
			DynamicBuffer data{};

			if (m_Renderer->GetCamera() != nullptr)
			{
				data.CameraPos = Vector4f(m_Renderer->GetCamera()->Parent->Transform->Position);
				data.Projection = m_Renderer->GetCamera()->ToProjectionMatrixLH;
				data.View = m_Renderer->GetCamera()->ToViewMatrixLH;
			}

			data.Time = Vector2f((float)m_Renderer->GetEngine()->TimeSinceStart);

			m_DynamicGlobalBuffer->Bind(&data);
		}
	}
}