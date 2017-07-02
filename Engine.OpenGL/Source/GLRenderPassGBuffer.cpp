#include "Include\OpenGL\RenderPasses\GLRenderPassGBuffer.h"

#include "Include\OpenGL\GLRenderer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLRenderPassGBuffer::GLRenderPassGBuffer(GLRenderer *a_Renderer)
			: GLRenderPass(a_Renderer)
		{
			m_GBuffer = std::make_unique<GLGbuffer>(m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height);
			m_Shadowbuffer = std::make_unique<GLShadowbuffer>(1024, 1024);

			SShaderContainerDesc containerDesc{};

			containerDesc.AddShader("GBufferFinal.vs");
			containerDesc.AddShader("GBufferFinal.fs");

			m_FinalShader = std::make_unique<GLShaderContainer>();
			m_FinalShader->Initialize(containerDesc, a_Renderer);

			STextureDesc desc{};
			desc.FilePath = "Assets/Textures/Vignette.tga";
			m_Vignette = static_cast<GLTexture*>(a_Renderer->GetCache()->LoadTexture(desc));

			m_ShadowCamera = std::make_unique<Camera>(50.0f, 1.0f, 300.0f);
		}

		void GLRenderPassGBuffer::Resize()
		{
			m_GBuffer = std::make_unique<GLGbuffer>(m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height);
		}

		void GLRenderPassGBuffer::RenderPass()
		{
			Scene::Transformation shadowPos = Scene::Transformation();
			shadowPos.Position = Vector3f(0, 150, 0);
			shadowPos.Rotation = Vector3f(-90,0, 0);
			m_ShadowCamera->UpdateOrthographic(shadowPos, -200, 200, -200, 200);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glClearColor(1, 1, 1, 1);

			m_Renderer->SetShaderStage(EShaderStage::DEPTH);

			// Shadow PASS
			m_Shadowbuffer->Bind();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_Container->Bind(m_ShadowCamera->ToProjectionMatrixLH * m_ShadowCamera->ToViewMatrixLH);
			
			m_Renderer->RenderScene();

			m_Shadowbuffer->Unbind();

			// SHADOW END

			m_Renderer->SetShaderStage(EShaderStage::NORMAL);

			// GBUFFER PASS

			m_GBuffer->Bind();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_Renderer->RenderScene();

			m_GBuffer->Unbind();

			// GBUFFER END 

			glViewport(0, 0, m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
			m_Shadowbuffer->RenderTargets["Depth"]->Bind();

			glActiveTexture(GL_TEXTURE6);
			m_FinalShader->SetInt("uVignette", 6);
			m_Vignette->Bind();

			glDisable(GL_CULL_FACE);
			RenderQuad();
			glEnable(GL_CULL_FACE);
		}
	}
}