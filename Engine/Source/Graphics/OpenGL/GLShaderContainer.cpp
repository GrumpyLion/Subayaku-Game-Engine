#include "GLShaderContainer.h"

#include "GLShader.h"
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

		bool GLShaderContainer::Initialize(Material *a_Material)
		{
			m_Program = glCreateProgram();

			//Shaders will be automatically destroyed after this scope. We don't need them anymore if they're bound to the program
			GLShader vertex = GLShader();
			GLShader fragment = GLShader();

			if (!vertex.Initialize(EShaderTypes::VertexShader, a_Material->VertexShader))
			{
				LogErr("Vertex Init failed");
				return false;
			}

			//Attach the Shaders to the program
			glAttachShader(m_Program, vertex.GetProgram());
			if (GetError())
				return false;

			if (!fragment.Initialize(EShaderTypes::FragmentShader, a_Material->FragmentShader))
			{
				LogErr("Fragment Init failed");
				return false;
			}

			//Attach the Shaders to the program
			glAttachShader(m_Program, fragment.GetProgram());
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
				LogErr("Uniform not found");
				LogErr(a_Name);
			}
			return result;
		}

		void GLShaderContainer::SetVector3f(const char* a_UniformName, const Vector3f &a_Vec)
		{
			glUniform3f(GetUniform(a_UniformName), a_Vec.x, a_Vec.y, a_Vec.z);
		}

		void GLShaderContainer::SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat)
		{
			glUniformMatrix4fv(GetUniform(a_UniformName), 1, GL_FALSE, &a_Mat.m11);
		}

		bool GLShaderContainer::GetError()
		{
			GLchar log[256]{};
			glGetProgramInfoLog(m_Program, 256, 0, log);
			if (strlen(log) > 0)
			{
				LogErr(log);
				return true;
			}
			return false;
		}
	}
}