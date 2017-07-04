#pragma once

#include "OpenGL\GLShaderContainer.h"
#include "OpenGL\GLFramebuffer.h"
#include "OpenGL\BufferContainers\GLShaderBufferShadows.h"

#include "GLRenderPass.h"

#include "Graphics\Camera.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderer;

		class GLRenderPassShadow : public GLRenderPass
		{
		private:
			// Depth buffer
			//
			std::unique_ptr<GLFramebuffer> m_Depthbuffer;

			// Used to blur the shadowmap for smooth shadows
			// 
			std::unique_ptr<GLFramebuffer> m_Tempbuffer;

			// Position of the shadows
			std::unique_ptr<Camera> m_ShadowCamera;

			// Blurrr
			//
			std::unique_ptr<GLShaderContainer> m_BlurShader;
			
			// LightSpaceMatrix
			//
			std::unique_ptr<GLShaderBufferShadows> m_ShaderBuffer;

			// Shadowmap Resolution
			//
			GLuint m_ShadowSize = 1024;

		public:
			GLRenderPassShadow(GLRenderer *a_Renderer);

			void RenderPass() final;
			void Resize() final;

			GLFramebuffer *GetBuffer() { return m_Depthbuffer.get(); }
		};
	}
}