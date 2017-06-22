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

			m_ParentTransform = a_Material->ParentTransform;

			m_Container = std::make_unique<D3DShaderContainer>();

			if (!m_Container->Initialize(a_Material->Shaders, a_Renderer))
				return false;

			for (auto &temp : a_Material->Textures)
			{
				D3DTexture *tex = static_cast<D3DTexture*>(m_Renderer->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsInvalid(tex))
					return false;

				m_Textures.insert({ tex->UniformName, tex });
			}

			return true;
		}

		void D3DMaterial::Bind()
		{
			for (auto &temp : m_Textures)
			{
				temp.second->Bind();
			}

			m_Container->BindProgram();
		}

		D3DShaderContainer *D3DMaterial::GetContainer()
		{		return m_Container.get();		}
	}
}