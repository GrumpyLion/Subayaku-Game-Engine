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
			float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };

			STextureDesc tempDesc{};
			std::unique_ptr<GLTexture> temp = std::make_unique<GLTexture>();
			
			tempDesc.Width = a_Width;
			tempDesc.Height = a_Height;
			tempDesc.Filter = ETextureFilter::NEAREST;
			tempDesc.IsFramebufferTexture = true;

			// Position data
			temp->InitializeFramebufferTexture(tempDesc, GL_RGB16F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, borderColor);

			AddAttachement("Position", std::move(temp));

			// Normal data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGB16F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT1, borderColor);

			AddAttachement("Normal", std::move(temp));
		
			// Albedo data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT2, borderColor);

			AddAttachement("Albedo", std::move(temp));

			// Specularity data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RG16F, GL_RG, GL_FLOAT, GL_COLOR_ATTACHMENT3, borderColor);

			AddAttachement("Specular", std::move(temp));

			// Fragpos in light space data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA32F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT4, borderColor);

			AddAttachement("PositionLightSpace", std::move(temp));

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}