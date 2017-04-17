#pragma once

#include <GLEW\Include\glew.h>
#include "GLEShaderTypes.h"
#include <string>

namespace Graphics
{
	namespace OpenGL
	{
		class GLShader
		{
		private:
			GLuint m_Handle = 0;

		public:
			EShaderTypes Type;
			
			~GLShader();
			bool Initialize(EShaderTypes a_Type, std::string a_FilePath);
			bool GetError();
			GLuint GetProgram() const;
		};
	}
}