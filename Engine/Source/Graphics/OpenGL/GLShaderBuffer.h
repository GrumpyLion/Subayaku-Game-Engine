#pragma once

#include "Math\Math.h"
#include "Graphics\Interface\IShaderBuffer.h"
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

			bool Initialize(SShaderBufferDesc a_Desc) override;
			void Bind(void* a_BufferData);
			void Unbind();
		};

	}
}