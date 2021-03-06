#pragma once

#include "Graphics\Interfaces\IShader.h"

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
			bool Initialize(SShaderDesc &a_Desc, IRenderer *a_Renderer) final;
			bool GetError();
			GLuint GetProgram() const;
		};
	}
}