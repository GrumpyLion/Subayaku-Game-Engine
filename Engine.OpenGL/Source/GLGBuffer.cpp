#include "Include\OpenGL\GLGBuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLGbuffer::GLGbuffer(GLuint a_Width, GLuint a_Height)
			: GLFramebuffer(a_Width, a_Height, true)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

			unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
			glDrawBuffers(5, attachments);

			STextureDesc tempDesc{};
			std::unique_ptr<GLTexture> temp = std::make_unique<GLTexture>();
			
			tempDesc.Width = a_Width;
			tempDesc.Height = a_Height;
			tempDesc.Filter = ETextureFilter::NEAREST;
			tempDesc.IsFramebufferTexture = true;

			// Position data
			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0);

			AddAttachement("Position", std::move(temp));

			// Normal data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT1);

			AddAttachement("Normal", std::move(temp));
		
			// Albedo data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT2);

			AddAttachement("Albedo", std::move(temp));

			// Specularity data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT3);

			AddAttachement("Specular", std::move(temp));

			// Fragpos in light space data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT4);

			AddAttachement("PositionLightSpace", std::move(temp));

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}