#pragma once

#include "OpenGL\GLShaderBuffer.h"

#include <memory>

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderer;

		class GLShaderBufferShadows
		{
		private:
			std::unique_ptr<GLShaderBuffer> m_ShaderBuffer;

#pragma pack(push, 1)
			struct ShadowBuffer
			{
				Matrix4f LightSpaceMatrix;
			};
#pragma pack(pop)

		public:
			GLShaderBufferShadows(GLRenderer *a_Renderer);
			void Bind(Matrix4f &a_LightMatrix);
		};
	}
}