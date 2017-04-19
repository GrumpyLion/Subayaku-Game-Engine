#include "GLMaterial.h"
#include "GLShaderContainer.h"
#include "Utilities\Utilities.h"
#include "Graphics\Material.h"

#include "Core\Engine.h"
#include "Graphics\Interface\IRenderer.h"
#include "GLRenderer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLMaterial::~GLMaterial()
		{
			SAFE_DELETE(m_Container);
		}

		bool GLMaterial::Initialize(Material *a_Material)
		{
			m_Container = new GLShaderContainer();

			if (!m_Container->Initialize(a_Material))
				return false;
			
			m_Renderer = static_cast<GLRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			return true;
		}

		void GLMaterial::Bind()
		{
			m_Container->BindProgram();

			m_Container->SetMatrix4f("uPRMatrix",
				Matrix4f::Perspective(m_Renderer->Camera->FOV, 1024 / 600, m_Renderer->Camera->Near, m_Renderer->Camera->Far));

		}

		GLShaderContainer *GLMaterial::GetContainer()
		{		return m_Container;		}
	}
}