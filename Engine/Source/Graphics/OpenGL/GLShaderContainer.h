#pragma once

#include <GLEW\Include\glew.h>
#include "Math\Math.h"

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

			GLint GetUniform(const char* a_Name);

		public:
			~GLShaderContainer();

			bool Initialize(Material *a_Material);

			void BindProgram();
			void UnbindProgram();
			bool GetError();

			void SetVector3f(const char* a_UniformName, const Vector3f &a_Vec);
			void SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat);

		};
	}
}