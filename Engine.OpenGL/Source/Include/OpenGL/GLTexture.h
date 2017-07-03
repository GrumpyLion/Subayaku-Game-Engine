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

			// Creates an simple texture
			//
			bool Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer) final;

			// Creates an texture and binds it into a framebuffer with the given attachement
			//
			bool InitializeFramebufferTexture(STextureDesc &a_Desc, GLenum a_Format, GLenum a_Format2, GLenum a_Type, GLenum a_Attachement, float* a_BorderColor);

			// Just binds it
			//
			void Bind();
			
			// Binds the texture into the currently bound framebuffer
			//
			void BindAsFramebufferTexture(GLenum a_Attachement);

			// Unbinds it
			//
			void Unbind();
		};
	}
}