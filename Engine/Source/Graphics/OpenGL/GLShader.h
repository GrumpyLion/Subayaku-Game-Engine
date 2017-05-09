#pragma once

#include "Graphics\Interface\IShader.h"

#include <GLEW\Include\glew.h>
#include <string>

namespace Graphics
{
	namespace OpenGL
	{
		class GLShader : public IShader
		{
		private:
			GLuint m_Handle = 0;

		public:
			EShaderType Type;
			
			~GLShader();
			bool Initialize(SShaderDesc &a_Desc) override;
			bool GetError();
			GLuint GetProgram() const;
		};
	}
}