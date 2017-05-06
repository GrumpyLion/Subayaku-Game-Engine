#include "GLMaterial.h"
#include "GLShaderContainer.h"
#include "Utilities\Utilities.h"
#include "Graphics\Material.h"

#include "Core\Engine.h"
#include "Graphics\Interface\IRenderer.h"
#include "GLRenderer.h"
#include "GLTexture.h"
#include "Core\Engine.h"
#include "GLHelper.h"
#include "Utilities\Cache.h"
#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLMaterial::~GLMaterial()
		{
			SafeDelete(m_Container);

			m_Textures.clear();
		}

		bool GLMaterial::Initialize(Material *a_Material)
		{
			m_Container = new GLShaderContainer();

			if (!m_Container->Initialize(a_Material))
				return false;
			
			m_FloatUniforms = a_Material->GetFloats();

			for (auto &temp : a_Material->GetTextures())
			{
				GLTexture *tex = dynamic_cast<GLTexture*>(Core::Engine::StaticClass()->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsValid(tex))
					return false;
				
				m_Textures.insert(std::pair<std::string, GLTexture*>(temp.second.UniformName, tex));
			}

			m_Renderer = static_cast<GLRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			//Set Engine uniforms
			m_FoundUniforms.insert(std::pair<std::string, bool>("uPRMatrix", true));
			m_FoundUniforms.insert(std::pair<std::string, bool>("uORMatrix", true));
			m_FoundUniforms.insert(std::pair<std::string, bool>("uVWMatrix", true));
			m_FoundUniforms.insert(std::pair<std::string, bool>("uTime", true));
			m_FoundUniforms.insert(std::pair<std::string, bool>("uCameraPos", true));
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
			
			if (m_FoundUniforms.find("uPRMatrix")->second)
			{
				if (CheckIfPointerIsValid(m_Renderer->Camera))
					return;
				if (!m_Container->SetMatrix4f("uPRMatrix", m_Renderer->Camera->ToProjectionMatrixLH()))
					m_FoundUniforms.find("uPRMatrix")->second = false;				
			}

			if (m_FoundUniforms.find("uORMatrix")->second)
			{
				if (!m_Container->SetMatrix4f("uORMatrix", Matrix4f::Orthograpic(0.0f, 4.0f, 0.0f, 2.5f, -1.0f, 10.0f)))
					m_FoundUniforms.find("uORMatrix")->second = false;
			}

			if (m_FoundUniforms.find("uVWMatrix")->second)
			{
				if (!m_Container->SetMatrix4f("uVWMatrix", m_Renderer->Camera->ToViewMatrixLH()))
					m_FoundUniforms.find("uVWMatrix")->second = false;
			}

			if (m_FoundUniforms.find("uTime")->second)
			{
				if (!m_Container->SetFloat("uTime", (float)Core::Engine::StaticClass()->GetTimeSinceStart()))
					m_FoundUniforms.find("uTime")->second = false;
			}

			if (m_FoundUniforms.find("uCameraPos")->second)
			{
				if (!m_Container->SetVector3f("uCameraPos", Core::Engine::StaticClass()->GetRenderer()->GetCamera()->Parent->Transform->Position))
					m_FoundUniforms.find("uCameraPos")->second = false;
			}
		}

		GLShaderContainer *GLMaterial::GetContainer()
		{		return m_Container;		}
	}
}