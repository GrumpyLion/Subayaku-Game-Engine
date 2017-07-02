#pragma once

#include "GLTexture.h"

#include <unordered_map>
#include <string>
#include <GLEW\Include\glew.h>

#include <memory>

namespace Graphics
{
	namespace OpenGL
	{
		class GLFramebuffer
		{
		protected:
			GLuint m_FBO = 0;
			GLuint m_RBO = 0;
			GLuint m_Width = 0, m_Height = 0;

		public:
			std::unordered_map<std::string, std::unique_ptr<GLTexture>> RenderTargets;

			virtual ~GLFramebuffer();
			GLFramebuffer(GLuint a_Width, GLuint a_Height, bool a_GenRenderBuffer);

			void AddAttachement(std::string a_Name, std::unique_ptr<GLTexture> a_Texture);
			void Bind();
			void Unbind();
		};
	}
}