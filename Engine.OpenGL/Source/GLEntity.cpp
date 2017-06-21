#include "OpenGL\GLEntity.h"

#include "OpenGL\GLShaderContainer.h"
#include "OpenGL\GLHelper.h"
#include "OpenGL\GLMesh.h"
#include "OpenGL\GLRenderer.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"

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

			//Add the first instance
			//
			m_Mesh->AddInstance(a_Desc.MeshRenderer);

			return true;
		}

		void GLEntity::AddInstance(Scene::CMeshRenderer *a_MeshRenderer)
		{
			if (a_MeshRenderer == nullptr)
				return;

			m_Mesh->AddInstance(a_MeshRenderer);
		}

		void GLEntity::RemoveInstance(Scene::CMeshRenderer *a_MeshRenderer)
		{
			if (a_MeshRenderer == nullptr)
				return;

			m_Mesh->RemoveInstance(a_MeshRenderer);
		}

		void GLEntity::Render()
		{
			m_Material->Bind();

			m_Mesh->Bind();

			if (m_Mesh->HasIndices)
			{
				if (m_Mesh->GetInstanceCount() == 1)
					glDrawElements(EMeshPrimitiveToGL(m_Mesh->Mode), m_Mesh->GetCount(), GL_UNSIGNED_INT, nullptr);
				else
					glDrawElementsInstanced(EMeshPrimitiveToGL(m_Mesh->Mode), m_Mesh->GetCount(), GL_UNSIGNED_INT, nullptr, (GLsizei)m_Mesh->GetInstanceCount());
			}
			else
			{
				if (m_Mesh->GetInstanceCount() == 1)
					glDrawArrays(EMeshPrimitiveToGL(m_Mesh->Mode), 0, m_Mesh->GetCount());
				else
					glDrawArraysInstanced(EMeshPrimitiveToGL(m_Mesh->Mode), 0, m_Mesh->GetCount(), (GLsizei)m_Mesh->GetInstanceCount());
			}
			
			m_Mesh->Unbind();
		}
	}
}