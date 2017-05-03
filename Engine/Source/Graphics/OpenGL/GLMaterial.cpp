#include "GLMaterial.h"
#include "GLShaderContainer.h"
#include "Utilities\Utilities.h"
#include "Graphics\Material.h"

#include "Core\Engine.h"
#include "Graphics\Interface\IRenderer.h"
#include "GLRenderer.h"
#include "GLTexture.h"
#include "Core\Engine.h"
#include "Graphics\Cache\TextureCache.h"
#include "Graphics\TextureInfo.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLMaterial::~GLMaterial()
		{
			SAFE_DELETE(m_Container);

			for (auto &temp : m_Textures)
			{
				delete temp.second;
			}
			m_Textures.clear();
		}

		bool GLMaterial::Initialize(Material *a_Material)
		{
			m_Container = new GLShaderContainer();

			if (!m_Container->Initialize(a_Material))
				return false;
			
			for (auto &temp : a_Material->GetTextures())
			{
				GLTexture *tex = new GLTexture();
				switch (temp.second.Filter)
				{
				case ETextureFilter::LINEAR:
					tex->InitializeFromCache(temp.first.c_str(), GL_LINEAR);
					break;

				case ETextureFilter::NEAREST:
					tex->InitializeFromCache(temp.first.c_str(), GL_NEAREST);
					break;
				}

				if (tex == nullptr)
					return false;
				
				m_Textures.insert(std::pair<std::string, GLTexture*>(temp.second.UniformName, tex));
			}

			m_Renderer = static_cast<GLRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			//Set Engine uniforms
			m_FoundUniforms.insert(std::pair<std::string, bool>("uPRMatrix", true));
			m_FoundUniforms.insert(std::pair<std::string, bool>("uORMatrix", true));
			return true;
		}

		void GLMaterial::Bind()
		{
			m_Container->BindProgram();

			int index = 0;
			for (auto &temp : m_Textures)
			{
				glActiveTexture(GL_TEXTURE0);
				temp.second->Bind();
				m_Container->SetInt(temp.first.c_str(), index);
				index++;
			}

			float aspect = (float)Core::Engine::StaticClass()->GetContext().Width / (float)Core::Engine::StaticClass()->GetContext().Height;

			if (m_FoundUniforms.find("uPRMatrix")->second)
			{
				if (m_Renderer->Camera == nullptr) 
					return;
				if (!m_Container->SetMatrix4f("uPRMatrix",
					Matrix4f::Perspective(m_Renderer->Camera->FOV,
					aspect, m_Renderer->Camera->Near, m_Renderer->Camera->Far)))
					m_FoundUniforms.find("uPRMatrix")->second = false;				
			}

			if (m_FoundUniforms.find("uORMatrix")->second)
			{
				if (!m_Container->SetMatrix4f("uORMatrix", Matrix4f::Orthograpic(0.0f, 4.0f, 0.0f, 2.5f, -1.0f, 10.0f)))
					m_FoundUniforms.find("uORMatrix")->second = false;
			}
		}

		GLShaderContainer *GLMaterial::GetContainer()
		{		return m_Container;		}
	}
}