#include "OpenGL\BufferContainers\GLShaderBufferShadows.h"
#include "OpenGL\GLRenderer.h"

#include "Graphics\Enums\GlobalIndices.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLShaderBufferShadows::GLShaderBufferShadows(GLRenderer *a_Renderer)
		{
			m_ShaderBuffer = std::make_unique<GLShaderBuffer>();

			SShaderBufferDesc desc{};
			desc.BufferIndex = EBufferIndex::ShadowBuffer;
			desc.BufferSize = sizeof(ShadowBuffer);
			desc.IsDynamic = true;

			m_ShaderBuffer->Initialize(desc, a_Renderer);

		}
		
		void GLShaderBufferShadows::Bind(Matrix4f &a_LightSpaceMatrix)
		{
			ShadowBuffer buffer{};

			buffer.LightSpaceMatrix = a_LightSpaceMatrix;
			
			m_ShaderBuffer->Bind(&buffer);
		}
	}
}