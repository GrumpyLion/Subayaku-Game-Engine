#include "GLEntity.h"

#include "GLShaderContainer.h"
#include "GLHelper.h"
#include "GLMesh.h"
#include "GLRenderer.h"

namespace Graphics
{
	namespace OpenGL
	{
		bool GLEntity::Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<GLRenderer*>(a_Renderer);

			m_Material = std::make_unique<GLMaterial>();
			m_Material->Initialize(a_Desc.Material, a_Renderer);

			m_Mesh = static_cast<GLMesh*>(m_Renderer->GetCache()->LoadMesh(a_Desc.Mesh));
				
			if (m_Mesh == nullptr)
				return false;			

			return true;
		}

		void GLEntity::Render()
		{
			m_Material->Bind();

			m_Mesh->Bind();

			if (m_Mesh->HasIndices)
			{
				glDrawElements(EMeshPrimitiveToGL(m_Mesh->Mode), m_Mesh->GetCount(), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				glDrawArrays(EMeshPrimitiveToGL(m_Mesh->Mode), 0, m_Mesh->GetCount());
			}
			
			m_Mesh->Unbind();
		}
	}
}