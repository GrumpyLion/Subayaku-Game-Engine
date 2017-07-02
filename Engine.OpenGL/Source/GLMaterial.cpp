#include "OpenGL\GLMaterial.h"
#include "OpenGL\GLHelper.h"
#include "OpenGL\GLRenderer.h"
#include "OpenGL\GLTexture.h"

namespace Graphics
{
	namespace OpenGL
	{
		bool GLMaterial::Initialize(Material *a_Material, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<GLRenderer*>(a_Renderer);
			
			for (auto &temp : a_Material->Shaders)
			{
				auto container = std::make_unique<GLShaderContainer>();

				if (!container->Initialize(temp.second, a_Renderer))
					return false;

				m_ShaderContainers.insert( { temp.first, std::move(container) } );
			}

			for (auto &temp : a_Material->Textures)
			{
				GLTexture *tex = static_cast<GLTexture*>(m_Renderer->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsInvalid(tex))
					return false;
				
				m_Textures.insert({ temp.second.UniformName, tex });
			}
			return true;
		}

		bool GLMaterial::Bind()
		{
			if (m_ShaderContainers[m_Renderer->GetShaderStage()] != nullptr)
				m_ShaderContainers[m_Renderer->GetShaderStage()]->BindProgram();
			else
				return false;

			if (m_Renderer->GetShaderStage() == EShaderStage::NORMAL)
			{
				int index = 0;
				for (auto &temp : m_Textures)
				{
					//TODO Check if the uniform was found 
					glActiveTexture(ActiveTextureIndex(index));
					temp.second->Bind();
					m_ShaderContainers[m_Renderer->GetShaderStage()]->SetInt(temp.first.c_str(), index);
					index++;
				}
			}

			return true;
		}

		GLShaderContainer *GLMaterial::GetContainer()
		{		return nullptr;		}
	}
}