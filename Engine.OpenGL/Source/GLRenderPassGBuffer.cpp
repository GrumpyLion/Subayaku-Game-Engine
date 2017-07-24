#include "Include\OpenGL\RenderPasses\GLRenderPassGBuffer.h"

#include "Include\OpenGL\RenderPasses\GLRenderPassShadow.h"

#include "Include\OpenGL\GLRenderer.h"
#include "Graphics\Enums\GlobalIndices.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLRenderPassGBuffer::GLRenderPassGBuffer(GLRenderer *a_Renderer)
			: GLRenderPass(a_Renderer)
		{
			// Init GBuffer
			//
			InitGBuffer();

			SShaderBufferDesc bufferDesc{};
			bufferDesc.BufferIndex = EBufferIndex::GlobalDynamicBuffer;
			bufferDesc.BufferSize = sizeof(DynamicBuffer);
			bufferDesc.IsDynamic = true;

			m_Container = std::make_unique<GLShaderBuffer>();
			m_Container->Initialize(bufferDesc, a_Renderer);

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

		void GLRenderPassGBuffer::InitGBuffer()
		{
			m_GBuffer = std::make_unique<GLFramebuffer>(m_Renderer->GetDescription().Width, m_Renderer->GetDescription().Height, true);

			m_GBuffer->Bind();

			unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
			glDrawBuffers(5, attachments);
			float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };

			STextureDesc tempDesc{};
			std::unique_ptr<GLTexture> temp = std::make_unique<GLTexture>();

			tempDesc.Width = m_Renderer->GetDescription().Width;
			tempDesc.Height = m_Renderer->GetDescription().Height;
			tempDesc.Filter = ETextureFilter::NEAREST;
			tempDesc.IsFramebufferTexture = true;

			// Position data
			temp->InitializeFramebufferTexture(tempDesc, GL_RGB16F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, borderColor);

			m_GBuffer->AddAttachement("Position", std::move(temp));

			// Normal data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGB16F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT1, borderColor);

			m_GBuffer->AddAttachement("Normal", std::move(temp));

			// Albedo data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT2, borderColor);

			m_GBuffer->AddAttachement("Albedo", std::move(temp));

			// Specularity data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RG16F, GL_RG, GL_FLOAT, GL_COLOR_ATTACHMENT3, borderColor);

			m_GBuffer->AddAttachement("Specular", std::move(temp));

			// Fragpos in light space data
			temp = std::make_unique<GLTexture>();

			temp->InitializeFramebufferTexture(tempDesc, GL_RGBA32F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT4, borderColor);

			m_GBuffer->AddAttachement("PositionLightSpace", std::move(temp));

			m_GBuffer->Unbind();
		}

		void GLRenderPassGBuffer::Resize()
		{
			InitGBuffer();
		}

		void GLRenderPassGBuffer::DynamicBufferPass()
		{
			DynamicBuffer data{};

			// Camera data
			//
			if (m_Renderer->GetCamera() != nullptr && m_Renderer->GetCamera())
			{
				data.CameraPos = Vector4f(m_Renderer->GetCamera()->Transform.Position);
				data.Projection = m_Renderer->GetCamera()->ToProjectionMatrixLH;
				data.View = m_Renderer->GetCamera()->ToViewMatrixLH;
			}

			//Direcitonal light stuff
			if (m_Renderer->GetDirectionalLight() != nullptr)
			{
				data.LightDirection = m_Renderer->GetDirectionalLight()->Parent->Transform->Position;
				data.LightColor = m_Renderer->GetDirectionalLight()->Color;
			}
			else
			{
				data.LightDirection = Vector4f(0, 0, 0, 0);
				data.LightColor = Vector4f(0, 0, 0, 0);
			}

			// Time in milliseconds since start
			//
			data.Time = Vector2f((float)m_Renderer->GetEngine()->TimeSinceStart);

			m_Container->Bind(&data);
		}

		void GLRenderPassGBuffer::RenderPass()
		{
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glClearColor(1, 1, 1, 1);

			DynamicBufferPass();

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