#pragma once

#include "OpenGL\GLShaderBuffer.h"
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
			std::unique_ptr<GLShaderBuffer> m_Container;

			std::unique_ptr<GLShaderContainer> m_FinalShader;
			GLTexture* m_Vignette = nullptr;

			void InitGBuffer();

#pragma pack(push, 1)
			struct DynamicBuffer
			{
				Matrix4f Projection;
				Matrix4f View;

				Vector4f CameraPos;
				Vector2f Time;

				Vector2f Padding01;

				//Directional Light -- 
				Vector4f LightDirection;
				Vector4f LightColor;
			};
#pragma pack(pop)

			void DynamicBufferPass();
		public:
			GLRenderPassGBuffer(GLRenderer *a_Renderer);

			void RenderPass() final;
			void Resize() final;
		};
	}
}