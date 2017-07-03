#include "Include\OpenGL\RenderPasses\GLRenderPassShadow.h"

#include "Include\OpenGL\GLRenderer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLRenderPassShadow::GLRenderPassShadow(GLRenderer *a_Renderer)
			: GLRenderPass(a_Renderer)
		{
			// Smaller values make better shadows
			//
			m_ShadowSize = 1024;

			m_Shadowbuffer = std::make_unique<GLShadowbuffer>(m_ShadowSize, m_ShadowSize);
			m_Tempbuffer = std::make_unique<GLTempbuffer>(m_ShadowSize, m_ShadowSize);

			// Simple gaussian blur shader
			//
			SShaderContainerDesc containerDesc{};

			containerDesc.AddShader("Filter.vs");
			containerDesc.AddShader("Filter.fs");

			m_BlurShader = std::make_unique<GLShaderContainer>();
			m_BlurShader->Initialize(containerDesc, a_Renderer);

			// FOV is not used here
			//
			m_ShadowCamera = std::make_unique<Camera>(0.0f, -50.0f, 500.0f);

			// Buffer for LightSpaceMatrix 
			m_ShaderBuffer = std::make_unique<GLShaderBufferShadows>(a_Renderer);
		}

		void GLRenderPassShadow::Resize()
		{
			// Empty. Shadow size does not scale
		}

		void GLRenderPassShadow::RenderPass()
		{
			Scene::Transformation shadowPos = Scene::Transformation();
			shadowPos.Position = Vector3f(0, 0, 0);
			shadowPos.Rotation = Vector3f(-65, 0, 0);
			m_ShadowCamera->UpdateOrthographic(shadowPos, -900.0f, 900.0f, -900.0f, 900.0f);

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			m_Renderer->SetShaderStage(EShaderStage::DEPTH);

			// Shadow PASS
			//
			m_Shadowbuffer->Bind();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ShaderBuffer->Bind(m_ShadowCamera->ToProjectionMatrixLH * m_ShadowCamera->ToViewMatrixLH);

			// Invert Cull face 
			//
			glFrontFace(GL_BACK);
			
			m_Renderer->RenderScene();
			
			glFrontFace(GL_FRONT);

			m_Shadowbuffer->Unbind();

			// SHADOW END
			//

			m_Renderer->SetShaderStage(EShaderStage::NORMAL);

			// BLUR PASS

			// Extra buffer
			//
			m_Tempbuffer->Bind();

			// Render to temporary texture
			//
			m_Tempbuffer->RenderTargets["Temp"]->BindAsFramebufferTexture(GL_COLOR_ATTACHMENT0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_BlurShader->BindProgram();

			glActiveTexture(GL_TEXTURE0);
			m_BlurShader->SetInt("uTexture", 0);
			
			// Take the depth texture
			//
			m_Shadowbuffer->RenderTargets["Depth"]->Bind();

			// Blur it horizontally
			//
			m_BlurShader->SetVector2f("uBlur", Vector2f(1.0f / (m_ShadowSize), 0.0f));

			RenderQuad();
			
			// Switch back to depth texture
			m_Shadowbuffer->RenderTargets["Depth"]->BindAsFramebufferTexture(GL_COLOR_ATTACHMENT0);
			m_BlurShader->SetVector2f("uBlur", Vector2f(0.0f, 1.0f / (m_ShadowSize)));

			glActiveTexture(GL_TEXTURE0);
			m_BlurShader->SetInt("uTexture", 0);
			m_Tempbuffer->RenderTargets["Temp"]->Bind();


			// Overwrite it and blur it vertically
			//
			RenderQuad();

			m_Tempbuffer->Unbind();

			// BLUR END
		}
	}
}