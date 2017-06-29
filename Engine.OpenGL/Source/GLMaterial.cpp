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

			m_Container = std::make_unique<GLShaderContainer>();

			if (!m_Container->Initialize(a_Material->Shaders, a_Renderer))
				return false;

			for (auto &temp : a_Material->Textures)
			{
				GLTexture *tex = static_cast<GLTexture*>(m_Renderer->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsInvalid(tex))
					return false;
				
				m_Textures.insert({ temp.second.UniformName, tex });
			}
			return true;
		}

		void GLMaterial::Bind()
		{
			m_Container->BindProgram();

			int index = 0;
			for (auto &temp : m_Textures)
			{
				//TODO Check if the uniform was found 
				glActiveTexture(ActiveTextureIndex(index));
				temp.second->Bind();
				m_Container->SetInt(temp.first.c_str(), index);
				index++;
			}
		}

		GLShaderContainer *GLMaterial::GetContainer()
		{		return m_Container.get();		}
	}
}