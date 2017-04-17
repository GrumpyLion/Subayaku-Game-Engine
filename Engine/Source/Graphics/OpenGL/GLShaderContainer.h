#pragma once

#include <GLEW\Include\glew.h>

namespace Graphics
{
	class Material;

	namespace OpenGL
	{
		class GLShader;

		class GLShaderContainer
		{
		private:
			GLuint m_Program = 0;

		public:
			~GLShaderContainer();

			bool Initialize(Material *a_Material);

			void BindProgram();
			void UnbindProgram();
			bool GetError();

		};
	}
}