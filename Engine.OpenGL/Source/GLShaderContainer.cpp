#include "GLShaderContainer.h"

#include "GLRenderer.h"

#include "Graphics\Material.h"
#include "Utilities\Utilities.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLShaderContainer::~GLShaderContainer()
		{
			glDeleteProgram(m_Program);
		}

		bool GLShaderContainer::Initialize(SShaderContainerDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<GLRenderer*>(a_Renderer);

			m_Program = glCreateProgram();

			GLShader *vertex = static_cast<GLShader*>(m_Renderer->GetCache()->LoadShader(a_Desc.Vertex));

			if (vertex == nullptr)
			{
				LogErr("Vertex Init failed\n");
				return false;
			}

			//Attach the Shaders to the program
			glAttachShader(m_Program, vertex->GetProgram());
			if (GetError())
				return false;

			GLShader *fragment = static_cast<GLShader*>(m_Renderer->GetCache()->LoadShader(a_Desc.Fragment));

			if (fragment == nullptr)
			{
				LogErr("Fragment Init failed\n");
				return false;
			}

			//Attach the Shaders to the program
			glAttachShader(m_Program, fragment->GetProgram());
			if (GetError())
				return false;

			glLinkProgram(m_Program);
			if (GetError())
				return false;			

			return true;
		}
		
		void GLShaderContainer::BindProgram()
		{
			glUseProgram(m_Program);
		}

		void GLShaderContainer::UnbindProgram()
		{
			glUseProgram(0);
		}

		GLint GLShaderContainer::GetUniform(const char* a_Name)
		{
			GLint result = glGetUniformLocation(m_Program, a_Name);
			if (result == -1)
			{
				LogErr("Uniform not found %s \n", a_Name);
			}
			return result;
		}

		bool GLShaderContainer::SetInt(const char* a_UniformName, const int a_Value)
		{
			if (GetUniform(a_UniformName) == -1)
				return false;
			glUniform1i(GetUniform(a_UniformName), a_Value);
			return true;
		}

		bool GLShaderContainer::SetFloat(const char* a_UniformName, const float a_Value)
		{
			if (GetUniform(a_UniformName) == -1)
				return false;
			glUniform1f(GetUniform(a_UniformName), a_Value);
			return true;
		}

		bool GLShaderContainer::SetVector2f(const char* a_UniformName, const Vector2f &a_Vec)
		{
			if (GetUniform(a_UniformName) == -1)
				return false;
			glUniform2f(GetUniform(a_UniformName), a_Vec.x, a_Vec.y);
			return true;
		}

		bool GLShaderContainer::SetVector3f(const char* a_UniformName, const Vector3f &a_Vec)
		{
			if (GetUniform(a_UniformName) == -1)
				return false;
			glUniform3f(GetUniform(a_UniformName), a_Vec.x, a_Vec.y, a_Vec.z);
			return true;
		}

		bool GLShaderContainer::SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat)
		{
			if (GetUniform(a_UniformName) == -1)
				return false;
			glUniformMatrix4fv(GetUniform(a_UniformName), 1, GL_FALSE, &a_Mat.m11);
			return true;
		}

		GLuint GLShaderContainer::GetProgram()
		{
			return m_Program;
		}

		bool GLShaderContainer::GetError()
		{
			GLchar log[256]{};
			glGetProgramInfoLog(m_Program, 256, 0, log);
			if (strlen(log) > 0)
			{
				LogErr("%s\n", log);
				return true;
			}
			return false;
		}
	}
}