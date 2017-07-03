#pragma once

#include "GLFramebuffer.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLTempbuffer : public GLFramebuffer
		{
		private:

		public:
			GLTempbuffer(GLuint a_Width, GLuint a_Height);

		};
	}
}