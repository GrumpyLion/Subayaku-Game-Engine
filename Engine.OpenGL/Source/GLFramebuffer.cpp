#include "Include\OpenGL\GLFramebuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLFramebuffer::~GLFramebuffer()
		{
			glDeleteFramebuffers(1, &m_FBO);
			glDeleteRenderbuffers(1, &m_RBO);
		}

		GLFramebuffer::GLFramebuffer(GLuint a_Width, GLuint a_Height, bool a_GenRenderBuffer)
		{
			m_Width = a_Width;
			m_Height = a_Height;

			glGenFramebuffers(1, &m_FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

			if (a_GenRenderBuffer)
			{
				glGenRenderbuffers(1, &m_RBO);
				glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, a_Width, a_Height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void GLFramebuffer::AddAttachement(std::string a_Name, std::unique_ptr<GLTexture> a_Texture)
		{
			RenderTargets.insert({ a_Name, std::move(a_Texture) });
		}

		void GLFramebuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glViewport(0, 0, m_Width, m_Height);
		}

		void GLFramebuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}