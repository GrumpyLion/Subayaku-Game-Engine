#include "OpenGL\BufferContainers\GLShaderBufferGlobal.h"

#include "OpenGL\GLRenderer.h"

#include "Graphics\Enums\GlobalIndices.h"
#include "Utilities\Utilities.h"
#include "Scene\GameObject\GameObject.h"

namespace Graphics
{
	namespace OpenGL
	{		
		GLShaderBufferGlobal::GLShaderBufferGlobal(GLRenderer *a_Renderer)
		{
			m_Renderer = a_Renderer;

			SShaderBufferDesc desc{};

			m_ConstantGlobalBuffer = std::make_unique<GLShaderBuffer>();

			m_DynamicGlobalBuffer = std::make_unique<GLShaderBuffer>();

			desc = SShaderBufferDesc{};
			desc.BufferIndex = EBufferIndex::GlobalDynamicBuffer;
			desc.BufferSize = sizeof(DynamicBuffer);
			desc.IsDynamic = true;

			m_DynamicGlobalBuffer->Initialize(desc, m_Renderer);
		}

		void GLShaderBufferGlobal::Bind()
		{
			DynamicBuffer data{};

			// Camera data
			//
			if (m_Renderer->GetCamera() != nullptr && m_Renderer->GetCamera())
			{
				data.CameraPos = Vector4f(m_Renderer->GetCamera()->Transform.Position);
				data.Projection = m_Renderer->GetCamera()->ToProjectionMatrixLH;
				data.View = m_Renderer->GetCamera()->ToViewMatrixLH;
			}

			//Direcitonal light stuff
			if (m_Renderer->GetDirectionalLight() != nullptr)
			{
				data.LightDirection = m_Renderer->GetDirectionalLight()->Parent->Transform->Position;
				data.LightColor = m_Renderer->GetDirectionalLight()->Color;
			}
			else
			{
				data.LightDirection = Vector4f(0, 0, 0, 0);
				data.LightColor = Vector4f(0, 0, 0, 0);
			}

			// Time in milliseconds since start
			//
			data.Time = Vector2f((float)m_Renderer->GetEngine()->TimeSinceStart);

			m_DynamicGlobalBuffer->Bind(&data);
		}
	}
}