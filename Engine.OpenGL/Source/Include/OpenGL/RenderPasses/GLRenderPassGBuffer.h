#pragma once

#include "OpenGL\BufferContainers\GLShaderBufferGlobal.h"
#include "OpenGL\GLShaderContainer.h"
#include "OpenGL\GLGBuffer.h"
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
			std::unique_ptr<GLGbuffer> m_GBuffer;
			std::unique_ptr<GLShaderBufferGlobal> m_Container;

			std::unique_ptr<GLShaderContainer> m_FinalShader;
			GLTexture* m_Vignette = nullptr;

		public:
			GLRenderPassGBuffer(GLRenderer *a_Renderer);

			void RenderPass() final;
			void Resize() final;
		};
	}
}