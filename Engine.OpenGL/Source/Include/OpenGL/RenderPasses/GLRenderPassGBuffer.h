#pragma once

#include "OpenGL\BufferContainers\GLShaderBufferGlobal.h"
#include "OpenGL\GLShaderContainer.h"
#include "OpenGL\GLFramebuffer.h"
#include "OpenGL\GLTexture.h"
#include "GLRenderPass.h"

#include "Graphics\Camera.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderer;

		class GLRenderPassGBuffer : public GLRenderPass
		{
		private:
			std::unique_ptr<GLFramebuffer> m_GBuffer;
			std::unique_ptr<GLShaderBufferGlobal> m_Container;

			std::unique_ptr<GLShaderContainer> m_FinalShader;
			GLTexture* m_Vignette = nullptr;

			void InitGBuffer();

		public:
			GLRenderPassGBuffer(GLRenderer *a_Renderer);

			void RenderPass() final;
			void Resize() final;
		};
	}
}