#include "Include\OpenGL\GLTempbuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLTempbuffer::GLTempbuffer(GLuint a_Width, GLuint a_Height)
			: GLFramebuffer(a_Width, a_Height, false)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

			STextureDesc tempDesc{};
			std::unique_ptr<GLTexture> temp = std::make_unique<GLTexture>();

			tempDesc.Width = a_Width;
			tempDesc.Height = a_Height;
			tempDesc.Filter = ETextureFilter::LINEAR;
			tempDesc.IsFramebufferTexture = true;

			// Position data
			float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
			temp->InitializeFramebufferTexture(tempDesc, GL_RG32F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0, borderColor);

			AddAttachement("Temp", std::move(temp));

			unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, attachments);
			glReadBuffer(GL_NONE);
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}