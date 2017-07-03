#include "Include\OpenGL\RenderPasses\GLRenderPassGBuffer.h"

#include "Include\OpenGL\RenderPasses\GLRenderPassShadow.h"

#include "Include\OpenGL\GLRenderer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLRenderPassGBuffer::GLRenderPassGBuffer(GLRenderer *a_Renderer)
			: GLRenderPass(a_Renderer)
		{
			m_GBuffer = std::make_unique<GLGbuffer>(m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height);
			
			m_Container = std::make_unique<GLShaderBufferGlobal>(a_Renderer);

			// Final Shader. It combines all income textures boii
			// 
			SShaderContainerDesc containerDesc{};

			containerDesc.AddShader("GBufferFinal.vs");
			containerDesc.AddShader("GBufferFinal.fs");

			m_FinalShader = std::make_unique<GLShaderContainer>();
			m_FinalShader->Initialize(containerDesc, a_Renderer);

			// A little PostFX
			//
			STextureDesc desc{};
			
			desc.FilePath = "Assets/Textures/Vignette.tga";
			
			m_Vignette = static_cast<GLTexture*>(a_Renderer->GetCache()->LoadTexture(desc));
		}

		void GLRenderPassGBuffer::Resize()
		{
			m_GBuffer = std::make_unique<GLGbuffer>(m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height);
		}

		void GLRenderPassGBuffer::RenderPass()
		{
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glClearColor(1, 1, 1, 1);

			m_Container->Bind();

			// GBUFFER PASS

			m_GBuffer->Bind();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_Renderer->RenderScene();

			m_GBuffer->Unbind();

			// GBUFFER END 

			// END PASS

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height);

			m_FinalShader->BindProgram();

			glActiveTexture(GL_TEXTURE0);
			m_FinalShader->SetInt("uAlbedo", 0);
			m_GBuffer->RenderTargets["Albedo"]->Bind();

			glActiveTexture(GL_TEXTURE1);
			m_FinalShader->SetInt("uNormal", 1);
			m_GBuffer->RenderTargets["Normal"]->Bind();

			glActiveTexture(GL_TEXTURE2);
			m_FinalShader->SetInt("uPosition", 2);
			m_GBuffer->RenderTargets["Position"]->Bind();

			glActiveTexture(GL_TEXTURE3);
			m_FinalShader->SetInt("uSpecular", 3);
			m_GBuffer->RenderTargets["Specular"]->Bind();

			glActiveTexture(GL_TEXTURE4);
			m_FinalShader->SetInt("uFragPosLightSpace", 4);
			m_GBuffer->RenderTargets["PositionLightSpace"]->Bind();

			glActiveTexture(GL_TEXTURE5);
			m_FinalShader->SetInt("uShadow", 5);
			if(static_cast<GLRenderPassShadow*>(m_Renderer->GetRenderPass("Shadow")) != nullptr)
				static_cast<GLRenderPassShadow*>(m_Renderer->GetRenderPass("Shadow"))->GetBuffer()->RenderTargets["Depth"]->Bind();

			glActiveTexture(GL_TEXTURE6);
			m_FinalShader->SetInt("uVignette", 6);
			m_Vignette->Bind();

			// Display the Result [:
			//
			RenderQuad();
		}
	}
}