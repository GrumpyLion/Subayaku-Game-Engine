#include "OpenGL\GLTexture.h"
#include "OpenGL\GLHelper.h"
#include "Utilities\Utilities.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLTexture::~GLTexture()
		{
			glDeleteTextures(1, &TextureID);
		}

		bool GLTexture::InitializeFramebufferTexture(STextureDesc &a_Desc, GLenum a_Format, GLenum a_Format2, GLenum a_Type, GLenum a_Attachement, float* a_BorderColor)
		{
			Width = a_Desc.Width;
			Height = a_Desc.Height;

			if (Width == 0 || Height == 0)
			{
				LogErr("Error while initializing GLTexture: Width Or Height is zero");
				return false;
			}

			glGenTextures(1, &TextureID);
			glBindTexture(GL_TEXTURE_2D, TextureID);
			// Set our texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, a_BorderColor);

			// Set texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ETextureFilterToGL(a_Desc));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ETextureFilterToGL(a_Desc));

			glTexImage2D(GL_TEXTURE_2D, 0, a_Format, a_Desc.Width, a_Desc.Height, 0, a_Format2, a_Type, nullptr);

			glFramebufferTexture2D(GL_FRAMEBUFFER, a_Attachement, GL_TEXTURE_2D, TextureID, 0);

			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}

		bool GLTexture::Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer)
		{
			Width = a_Desc.Width;
			Height = a_Desc.Height;

			if (Width == 0 || Height == 0)
			{
				LogErr("Error while initializing GLTexture: Width Or Height is zero");
				return false;
			}

			if (a_Desc.PixelData.size() == 0)
			{
				LogErr("Error while initializing GLTexture: PixelCount is zero");
				return false;
			}

			glGenTextures(1, &TextureID);
			glBindTexture(GL_TEXTURE_2D, TextureID);
			// Set our texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			// Set texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ETextureFilterToGL(a_Desc));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ETextureFilterToGL(a_Desc));

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_Desc.Width, a_Desc.Height, 0, ETextureFormatToGL(a_Desc), GL_UNSIGNED_BYTE, a_Desc.PixelData.data());
			
			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}

		void GLTexture::Bind()
		{
			glBindTexture(GL_TEXTURE_2D, TextureID);
		}

		void GLTexture::BindAsFramebufferTexture(GLenum a_Attachement)
		{
			glBindTexture(GL_TEXTURE_2D, TextureID);

			glFramebufferTexture2D(GL_FRAMEBUFFER, a_Attachement, GL_TEXTURE_2D, TextureID, 0);
		}

		void GLTexture::Unbind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}