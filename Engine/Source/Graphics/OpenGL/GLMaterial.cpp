#include "GLMaterial.h"
#include "GLHelper.h"
#include "Graphics\Material.h"
#include "GLRenderer.h"
#include "GLTexture.h"

#include "Utilities\Utilities.h"
#include "Core\Engine.h"
#include "Graphics\Interface\IRenderer.h"
#include "Core\Engine.h"
#include "Utilities\Cache.h"
#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	namespace OpenGL
	{
		bool GLMaterial::Initialize(Material *a_Material)
		{
			m_Container = std::make_unique<GLShaderContainer>();

			if (!m_Container->Initialize(a_Material->Shaders))
				return false;

			m_FloatUniforms = a_Material->GetFloats();

			for (auto &temp : a_Material->GetTextures())
			{
				GLTexture *tex = static_cast<GLTexture*>(Core::Engine::StaticClass()->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsInvalid(tex))
					return false;
				
				m_Textures.insert({ temp.second.UniformName, tex });
			}

			m_Renderer = static_cast<GLRenderer*>(Core::Engine::StaticClass()->GetRenderer());
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

			for (auto &temp : m_FloatUniforms)
			{
				//TODO Check if the uniform was found 
				m_Container->SetFloat(temp.first.c_str(), temp.second);
			}
		}

		GLShaderContainer *GLMaterial::GetContainer()
		{		return m_Container.get();		}
	}
}