#pragma once

#include "GLFramebuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLShadowbuffer : public GLFramebuffer
		{
		private:

		public:
			GLShadowbuffer(GLuint a_Width, GLuint a_Height);

		};
	}
}