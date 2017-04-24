#include "GLShader.h"
#include "Utilities\Utilities.h"
#include <fstream>

namespace Graphics
{
	namespace OpenGL
	{
		GLShader::~GLShader()
		{
			glDeleteShader(m_Handle);
		}

		bool GLShader::Initialize(EShaderTypes a_Type, std::string a_FilePath)
		{
			Type = a_Type;

			std::ifstream input(a_FilePath);

			std::string source((std::istreambuf_iterator<char>(input)),
				std::istreambuf_iterator<char>());

			if (!input.good())
			{
				LogErr("Shader File not found %s\n", a_FilePath);
				return false;
			}

			GLenum type = 0;
			
			switch (Type)
			{
			case EShaderTypes::VertexShader:
				type = GL_VERTEX_SHADER;
				break;
			case EShaderTypes::FragmentShader:
				type = GL_FRAGMENT_SHADER;
				break;
			default:
				//TODO ADD MORE TYPES
				LogErr("Undefined shader type\n");
				return false;
			}

			m_Handle = glCreateShader(type);
			if (m_Handle == 0)
			{
				LogErr("glCreateShader Failed\n");
				return false;
			}

			//Bind the Shader src into opengl
			const GLchar* src = reinterpret_cast<const GLchar*>(source.c_str());
			glShaderSource(m_Handle, 1, &src, 0);
			if (GetError())
				return false;

			//compile and check for errors
			glCompileShader(m_Handle);
			if (GetError())
				return false;

			//everything is fine :)
			return true;
		}

		bool GLShader::GetError()
		{
			GLchar log[256]{};
			glGetShaderInfoLog(m_Handle, 256, 0, log);
			if (strlen(log) > 0)
			{
				LogErr("%s\n", log);
				return true;
			}
			return false;
		}

		GLuint GLShader::GetProgram() const
		{
			return m_Handle;
		}

	}
}