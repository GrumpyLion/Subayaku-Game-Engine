#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Interfaces\IShaderContainer.h"
#include "GLShader.h"

namespace Graphics
{
	class Material;

	namespace OpenGL
	{
		class GLRenderer;

		class GLShaderContainer : public IShaderContainer
		{
	
		private:
			GLuint m_Program = 0;
			GLRenderer *m_Renderer = nullptr;

			GLint GetUniform(const char* a_Name);

		public:
			~GLShaderContainer();

			bool Initialize(SShaderContainerDesc &a_Desc, IRenderer *a_Renderer) override;

			void BindProgram() override;
			void UnbindProgram() override;
			bool GetError() override;

			GLuint GetProgram();

			bool SetInt(const char* a_UniformName, const int a_Value);
			bool SetFloat(const char* a_UniformName, const float a_Value);
			bool SetVector2f(const char* a_UniformName, const Vector2f &a_Vec);
			bool SetVector3f(const char* a_UniformName, const Vector3f &a_Vec);
			bool SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat);

		};
	}
}