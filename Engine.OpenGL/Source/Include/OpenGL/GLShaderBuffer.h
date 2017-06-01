#pragma once

#include "Math\Math.h"
#include "Graphics\Interfaces\IShaderBuffer.h"
#include <GLEW\Include\glew.h>

namespace Graphics
{
	namespace OpenGL 
	{
		class GLShaderBuffer : public IShaderBuffer
		{
		private:
			SShaderBufferDesc m_Desc{};
			GLuint m_UBO = 0;

		public:
			~GLShaderBuffer();

			bool Initialize(SShaderBufferDesc &a_Desc, IRenderer *a_Renderer) final;
			void Bind(void* a_BufferData);
			void Unbind();
		};

	}
}