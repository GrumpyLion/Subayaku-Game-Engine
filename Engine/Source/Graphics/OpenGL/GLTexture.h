#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Cache\TextureEnums.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLTexture
		{
		public:
			GLuint TextureID = 0;
			GLuint Width = 0;
			GLuint Height = 0;

			bool InitializeFromCache(const char* a_FileName, GLint a_Filter);
			bool Initialize(unsigned char* a_PixelData, ETextureFormat a_Format, GLenum a_DataType, GLint a_Filter, GLuint a_Width, GLuint a_Height);

			void Bind();
			void Unbind();

			~GLTexture();
		};
	}
}