#pragma once

#include "OpenGL\GLShaderBufferContainer.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderer;

		class GLRenderPass
		{
		protected:
			GLRenderer *m_Renderer = nullptr;

			std::unique_ptr<GLShaderBufferContainer> m_Container;

			GLuint m_QuadVAO = 0;
			GLuint m_QuadVBO = 0;

			// Renders a simple quad. Needed for post FX and displaying textures
			//
			void RenderQuad() 
			{
				if (m_QuadVAO == 0)
				{
					float quadVertices[] = {
						// positions        // texture Coords
						-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
						-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
						1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
						1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
					};
					// setup plane VAO
					glGenVertexArrays(1, &m_QuadVAO);
					glGenBuffers(1, &m_QuadVBO);
					glBindVertexArray(m_QuadVAO);
					glBindBuffer(GL_ARRAY_BUFFER, m_QuadVBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
				}
				glBindVertexArray(m_QuadVAO);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				glBindVertexArray(0);
			}

		public:
			virtual ~GLRenderPass()
			{	}

			GLRenderPass(GLRenderer * a_Renderer)
				: m_Renderer(a_Renderer)
			{
				m_Container = std::make_unique<GLShaderBufferContainer>();
				m_Container->Initialize(a_Renderer);
			}

			virtual void Resize() = 0;
			virtual void RenderPass() = 0; 
		};
	}
}