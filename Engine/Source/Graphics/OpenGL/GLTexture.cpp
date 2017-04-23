#include "GLTexture.h"
#include "Core\Engine.h"
#include "Graphics\Cache\TextureCache.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLTexture::~GLTexture()
		{
			glDeleteTextures(1, &TextureID);
		}
		
		bool GLTexture::InitializeFromCache(const char* a_FileName, GLint a_Filter)
		{
			TextureData<unsigned char*> *temp = Core::Engine::StaticClass()->GetTextureCache()->GetTexture(a_FileName);
			
			if (temp == nullptr)
				return false;

			return GLTexture::Initialize(temp->PixelData, temp->Format, GL_UNSIGNED_BYTE, a_Filter, temp->Width, temp->Height);			
		}

		bool GLTexture::Initialize(unsigned char* a_PixelData,
			ETextureFormat a_Format, GLenum a_DataType, GLint a_Filter, GLuint a_Width, GLuint a_Height)
		{
			Width = a_Width;
			Height = a_Height;

			GLenum format;
			switch (a_Format)
			{
			case ETextureFormat::RGBA:
				format = GL_RGBA;
				break;

			case ETextureFormat::RGB:
				format = GL_RGB;
				break;

			case ETextureFormat::RG:
				format = GL_RG;
				break;

			case ETextureFormat::R:
				format = GL_R;
				break;
			}

			glGenTextures(1, &TextureID);
			glBindTexture(GL_TEXTURE_2D, TextureID);
			// Set our texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// Set texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, a_Filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, a_Filter);

			glTexImage2D(GL_TEXTURE_2D, 0, format, a_Width, a_Height, 0, format, a_DataType, a_PixelData);

			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}

		void GLTexture::Bind()
		{
			glBindTexture(GL_TEXTURE_2D, TextureID);
		}

		void GLTexture::Unbind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}