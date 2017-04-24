#include "GLEntity.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"

#include "Utilities\Utilities.h"

#include "GLMaterial.h"
#include "GLMesh.h"
#include "GLShaderContainer.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLEntity::~GLEntity()
		{
			SAFE_DELETE(m_Material);
			SAFE_DELETE(m_Mesh);
		}

		bool GLEntity::Initialize(Mesh *a_Mesh, Material *a_Material, Scene::GameObject *a_Parent)
		{
			m_Parent = a_Parent;

			m_Material = new GLMaterial();
			if (!m_Material->Initialize(a_Material))
				return false;

			m_Mesh = new GLMesh();
			m_Mesh->Initialize(a_Mesh);

			return true;
		}

		float rot;
		void GLEntity::Render()
		{
			rot += 0.001f;
			m_Material->Bind();
			m_Mesh->Bind();
			
			Matrix4f temp = Matrix4f::Identity();
			temp *= Matrix4f::Scale(m_Parent->Transform->Scale);
			temp *= Matrix4f::Translate(m_Parent->Transform->Position);
			temp *= Matrix4f::RotateX(rot);

			m_Material->GetContainer()->SetMatrix4f("uMLMatrix", temp);

			glDrawElements(GL_TRIANGLES, m_Mesh->GetCount(), GL_UNSIGNED_INT, NULL);
			m_Mesh->Unbind();
		}
	}
}