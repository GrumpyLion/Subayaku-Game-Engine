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