#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Interfaces\ITexture.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLTexture : public ITexture
		{
		public:
			~GLTexture();

			GLuint TextureID = 0;
			GLuint Width = 0;
			GLuint Height = 0;

			bool Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer) final;

			bool InitializeFramebufferTexture(STextureDesc &a_Desc, GLenum a_Format, GLenum a_Type, GLenum a_Attachement);

			void Bind();
			void Unbind();

		};
	}
}