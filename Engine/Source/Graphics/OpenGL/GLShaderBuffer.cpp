#include "GLShaderBuffer.h"

#include <memory>

namespace Graphics
{
	namespace OpenGL
	{
		GLShaderBuffer::~GLShaderBuffer()
		{
			glDeleteBuffers(1, &m_UBO);
		}

		bool GLShaderBuffer::Initialize(SShaderBufferDesc a_Desc)
		{
			m_Desc = a_Desc;

			glGenBuffers(1, &m_UBO);
			glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
			glBufferData(GL_UNIFORM_BUFFER, m_Desc.BufferSize, nullptr, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			
			glBindBufferBase(GL_UNIFORM_BUFFER, m_Desc.BufferIndex, m_UBO);

			return true;
		}

		void GLShaderBuffer::Bind(void* a_BufferData)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);

			GLvoid* p = glMapBufferRange(GL_UNIFORM_BUFFER, 0, m_Desc.BufferSize, GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_WRITE_BIT);
			memcpy(p, a_BufferData, m_Desc.BufferSize);

			glUnmapBuffer(GL_UNIFORM_BUFFER);
		}

		void GLShaderBuffer::Unbind()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
}