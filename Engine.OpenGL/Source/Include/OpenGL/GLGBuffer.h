#pragma once

#include "GLFramebuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLGbuffer : public GLFramebuffer
		{
		private:

		public:
			GLGbuffer(GLuint a_Width, GLuint a_Height);
		};
	}
}
