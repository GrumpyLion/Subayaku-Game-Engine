#include "GLEntity.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"

#include "Core\Engine.h"
#include "Utilities\Utilities.h"
#include "Utilities\Cache.h"

#include "GLMaterial.h"
#include "GLMesh.h"
#include "GLShaderContainer.h"
#include "GLHelper.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLEntity::~GLEntity()
		{
			SafeDelete(m_Material);
			if(m_IsPrimitive)
				SafeDelete(m_Mesh);
		}

		bool GLEntity::Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent)
		{
			m_Parent = a_Parent;

			m_Material = new GLMaterial();
			if (!m_Material->Initialize(a_Material))
				return false;

			if (a_Mesh.Vertices.size() == 0)
			{
				m_IsPrimitive = false;
				m_Mesh = dynamic_cast<GLMesh*>(Core::Engine::StaticClass()->GetCache()->LoadMesh(a_Mesh));
			}
			else
			{
				m_IsPrimitive = true;
				m_Mesh = new GLMesh();
				m_Mesh->Initialize(a_Mesh);
			}
			return true;
		}

		void GLEntity::Render()
		{
			m_Material->Bind();
			m_Mesh->Bind();

			Matrix4f temp = Matrix4f::Identity();
			temp *= Matrix4f::Scale(m_Parent->Transform->Scale);
			temp *= Matrix4f::Translate(m_Parent->Transform->Position);
			temp *= Matrix4f::RotateX(m_Parent->Transform->Rotation.x * DEGTORAD);
			temp *= Matrix4f::RotateY(m_Parent->Transform->Rotation.y * DEGTORAD);
			temp *= Matrix4f::RotateZ(m_Parent->Transform->Rotation.z * DEGTORAD);

			m_Material->GetContainer()->SetMatrix4f("uMLMatrix", temp);
			
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