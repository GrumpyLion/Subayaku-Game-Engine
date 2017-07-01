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

		GLFramebuffer::GLFramebuffer(GLuint a_Width, GLuint a_Height)
		{
			glGenFramebuffers(1, &m_FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

			unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
			glDrawBuffers(3, attachments);

			glGenRenderbuffers(1, &m_RBO);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, a_Width, a_Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void GLFramebuffer::AddAttachement(std::string a_Name, std::unique_ptr<GLTexture> a_Texture)
		{
			m_TextureCount++;

			RenderTargets.insert({ a_Name, std::move(a_Texture) });
		}

		void GLFramebuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		}

		void GLFramebuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}