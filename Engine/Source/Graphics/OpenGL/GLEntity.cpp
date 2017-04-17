#include "GLEntity.h"

#include "Utilities\Utilities.h"

#include "GLMaterial.h"
#include "GLMesh.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLEntity::~GLEntity()
		{
			SAFE_DELETE(m_Material);
			SAFE_DELETE(m_Mesh);
		}

		bool GLEntity::Initialize(Mesh *a_Mesh, Material *a_Material)
		{
			m_Material = new GLMaterial();
			if (!m_Material->Initialize(a_Material))
				return false;

			m_Mesh = new GLMesh();
			m_Mesh->Initialize(a_Mesh);

			return true;
		}

		void GLEntity::Render()
		{
			m_Material->Bind();
			m_Mesh->Bind();
			glDrawElements(GL_TRIANGLES, m_Mesh->GetCount(), GL_UNSIGNED_INT, NULL);
			m_Mesh->Unbind();
		}
	}
}