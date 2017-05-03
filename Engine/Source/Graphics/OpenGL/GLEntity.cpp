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

		void GLEntity::Render()
		{
			m_Material->Bind();
			m_Mesh->Bind();
			
			Matrix4f temp = Matrix4f::Identity();
			temp *= Matrix4f::Scale(m_Parent->Transform->Scale);
			temp *= Matrix4f::Translate(m_Parent->Transform->Position);
			temp *= Matrix4f::RotateX(m_Parent->Transform->Rotation.x);
			temp *= Matrix4f::RotateY(m_Parent->Transform->Rotation.y);
			temp *= Matrix4f::RotateZ(m_Parent->Transform->Rotation.z);

			m_Material->GetContainer()->SetMatrix4f("uMLMatrix", temp);

			GLenum mode;
			switch (m_Mesh->Mode)
			{
			case EMeshPrimitive::TRIANGLES:
				mode = GL_TRIANGLES;
				break;

			case EMeshPrimitive::TRIANGLE_STRIP:
				mode = GL_TRIANGLE_STRIP;
				break;

			case EMeshPrimitive::LINES:
				mode = GL_LINES;
				break;

			case EMeshPrimitive::TRIANGLE_FAN:
				mode = GL_TRIANGLE_FAN;
				break;

			case EMeshPrimitive::POINTS:
				mode = GL_POINTS;
				break;
			}

			if (m_Mesh->HasIndices)
			{
				glDrawElements(mode, m_Mesh->GetCount(), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				glDrawArrays(mode, 0, m_Mesh->GetCount());
			}
			
			m_Mesh->Unbind();
		}
	}
}