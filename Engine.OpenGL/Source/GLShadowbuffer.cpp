#include "Include\OpenGL\GLShadowbuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLShadowbuffer::GLShadowbuffer(GLuint a_Width, GLuint a_Height)
			: GLFramebuffer(a_Width, a_Height, false)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

			STextureDesc tempDesc{};
			std::unique_ptr<GLTexture> temp = std::make_unique<GLTexture>();

			tempDesc.Width = a_Width;
			tempDesc.Height = a_Height;
			tempDesc.Filter = ETextureFilter::NEAREST;
			tempDesc.IsFramebufferTexture = true;

			// Position data
			temp->InitializeFramebufferTexture(tempDesc, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT);

			AddAttachement("Depth", std::move(temp));

			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}