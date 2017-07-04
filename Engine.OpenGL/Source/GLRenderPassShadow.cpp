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

			// TEMPBUFFER
			//
			m_Tempbuffer = std::make_unique<GLFramebuffer>(m_ShadowSize, m_ShadowSize, false);
			
			m_Tempbuffer->Bind();

			STextureDesc tempDesc{};
			std::unique_ptr<GLTexture> temp = std::make_unique<GLTexture>();

			tempDesc.Width = m_ShadowSize;
			tempDesc.Height = m_ShadowSize;
			tempDesc.Filter = ETextureFilter::LINEAR;
			tempDesc.IsFramebufferTexture = true;

			// Position data
			float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
			temp->InitializeFramebufferTexture(tempDesc, GL_RG32F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0, borderColor);

			m_Tempbuffer->AddAttachement("Temp", std::move(temp));

			unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, attachments);
			glReadBuffer(GL_NONE);

			m_Tempbuffer->Unbind();

			// TEMPBUFFER
			//

			m_Depthbuffer = std::make_unique<GLFramebuffer>(m_ShadowSize, m_ShadowSize, true);
			m_Depthbuffer->Bind();

			tempDesc = STextureDesc();
			temp = std::make_unique<GLTexture>();

			tempDesc.Width = m_ShadowSize;
			tempDesc.Height = m_ShadowSize;
			tempDesc.Filter = ETextureFilter::LINEAR;
			tempDesc.IsFramebufferTexture = true;

			temp->InitializeFramebufferTexture(tempDesc, GL_RG32F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0, borderColor);

			m_Depthbuffer->AddAttachement("Depth", std::move(temp));

			glDrawBuffers(1, attachments);
			glReadBuffer(GL_NONE);

			m_Depthbuffer->Unbind();

			// Simple gaussian blur shader
			//
			SShaderContainerDesc containerDesc{};

			containerDesc.AddShader("Shadow/Filter.vs");
			containerDesc.AddShader("Shadow/Filter.fs");

			m_BlurShader = std::make_unique<GLShaderContainer>();
			m_BlurShader->Initialize(containerDesc, a_Renderer);

			// FOV is not used here
			//
			m_ShadowCamera = std::make_unique<Camera>(0.0f, 100.0f, 500.0f);

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
			
			//if(m_Renderer->GetCamera() != nullptr)
			//	shadowPos.Position = Vector3f(m_Renderer->GetCamera()->Transform.Position * Vector3f(1, 0, 1));
			
			shadowPos.Rotation = Vector3f(280, 0, 0);
			m_ShadowCamera->UpdateOrthographic(shadowPos, -900.0f, 900.0f, -900.0f, 900.0f);

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			m_Renderer->SetShaderStage(EShaderStage::DEPTH);

			// Shadow PASS
			//
			m_Depthbuffer->Bind();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ShaderBuffer->Bind(m_ShadowCamera->ToProjectionMatrixLH * m_ShadowCamera->ToViewMatrixLH);

			// Invert Cull face 
			//
			
			//glFrontFace(GL_FRONT);
			glDisable(GL_CULL_FACE);
			
			m_Renderer->RenderScene();

			//glFrontFace(GL_BACK);
			glEnable(GL_CULL_FACE);

			m_Depthbuffer->Unbind();

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
			m_Depthbuffer->RenderTargets["Depth"]->Bind();

			// Blur it horizontally
			//
			m_BlurShader->SetVector2f("uBlur", Vector2f(1.0f / (m_ShadowSize), 0.0f));

			RenderQuad();
			
			// Switch back to depth texture
			m_Depthbuffer->RenderTargets["Depth"]->BindAsFramebufferTexture(GL_COLOR_ATTACHMENT0);
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