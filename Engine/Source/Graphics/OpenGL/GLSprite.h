#pragma once

#include <GLEW\Include\glew.h>
#include "Math\Math.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLShaderContainer;
		class GLTexture;

		class GLSprite
		{
		private:
			GLTexture *m_Texture = nullptr;

			GLuint m_VAO = 0;
			GLuint m_VBO = 0;
			GLuint m_IBO = 0;
			GLuint m_TBO = 0;

			GLShaderContainer *m_SpriteShader = nullptr;

		public:
			~GLSprite();
			bool Initialize();
			void Render();
		};
	}
}