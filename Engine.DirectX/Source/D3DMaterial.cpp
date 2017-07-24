#include "DirectX\D3DMaterial.h"
#include "DirectX\D3DHelper.h"
#include "DirectX\D3DRenderer.h"

namespace Graphics
{
	namespace DirectX
	{		
		bool D3DMaterial::Initialize(Material *a_Material, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);
			
			for (auto &temp : a_Material->Shaders)
			{
				auto container = std::make_unique<D3DShaderContainer>();

				if (!container->Initialize(temp.second, a_Renderer))
					return false;

				m_ShaderContainers.insert({ temp.first, std::move(container) });
			}

			for (auto &temp : a_Material->Textures)
			{
				D3DTexture *tex = static_cast<D3DTexture*>(m_Renderer->GetCache()->LoadTexture(temp.second));

				if (tex == nullptr)
					return false;

				m_Textures.insert({ tex->UniformName, tex });
			}

			return true;
		}

		bool D3DMaterial::Bind()
		{
			if (m_ShaderContainers[m_Renderer->GetShaderStage()] != nullptr)
				m_ShaderContainers[m_Renderer->GetShaderStage()]->BindProgram();
			else
				return false;
			
			for (auto &temp : m_Textures)
			{
				temp.second->Bind();
			}
						
			return true;
		}

		D3DShaderContainer *D3DMaterial::GetContainer()
		{	return m_ShaderContainers[m_Renderer->GetShaderStage()].get();		}
	}
}