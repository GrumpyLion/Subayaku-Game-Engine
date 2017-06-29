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
			m_Mesh->AddInstance(a_Desc.Transform);

			return true;
		}

		void GLEntity::AddInstance(Matrix4f *a_Transform)
		{
			if (a_Transform == nullptr)
				return;

			m_Mesh->AddInstance(a_Transform);
		}

		void GLEntity::RemoveInstance(Matrix4f *a_Transform)
		{
			if (a_Transform == nullptr)
				return;

			m_Mesh->RemoveInstance(a_Transform);
		}

		void GLEntity::Render()
		{
			m_Material->Bind();

			m_Mesh->Bind();

			if (m_Mesh->HasIndices)
			{
				if (m_Mesh->GetInstanceCount() == 1)
					glDrawElements(EMeshPrimitiveToGL(m_Mesh->Mode), m_Mesh->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
				else
					glDrawElementsInstanced(EMeshPrimitiveToGL(m_Mesh->Mode), m_Mesh->GetVertexCount(), GL_UNSIGNED_INT, nullptr, (GLsizei)m_Mesh->GetFrustumInstanceCount());
			}
			else
			{
				if (m_Mesh->GetInstanceCount() == 1)
					glDrawArrays(EMeshPrimitiveToGL(m_Mesh->Mode), 0, m_Mesh->GetVertexCount());
				else
					glDrawArraysInstanced(EMeshPrimitiveToGL(m_Mesh->Mode), 0, m_Mesh->GetVertexCount(), (GLsizei)m_Mesh->GetFrustumInstanceCount());
			}
			
			m_Mesh->Unbind();
		}
	}
}