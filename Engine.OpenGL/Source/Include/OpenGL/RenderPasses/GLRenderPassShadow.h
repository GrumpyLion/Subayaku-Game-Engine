#pragma once

#include "OpenGL\GLShaderContainer.h"
#include "OpenGL\GLShadowbuffer.h"
#include "OpenGL\GLTempbuffer.h"
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
			std::unique_ptr<GLShadowbuffer> m_Shadowbuffer;
			
			// Used to blur the shadowmap for smooth shadows
			// 
			std::unique_ptr<GLTempbuffer> m_Tempbuffer;

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

			GLShadowbuffer *GetBuffer() { return m_Shadowbuffer.get(); }
		};
	}
}