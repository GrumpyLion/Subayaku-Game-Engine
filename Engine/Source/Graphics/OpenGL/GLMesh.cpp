#include "GLMesh.h"
#include "Graphics\Mesh.h"
#include "Math\Math.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLMesh::~GLMesh()
		{
			glDeleteBuffers(numVBOs, m_VBOs);
			glDeleteVertexArrays(1, &m_VAO);
		}

		void GLMesh::Initialize(Mesh *a_Mesh)
		{
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			for (int i = 0; i < numVBOs; i++)
				m_VBOs[i] = 0;

			if (a_Mesh->Vertices.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[0]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);

				glBufferData(GL_ARRAY_BUFFER, a_Mesh->Vertices.size() * sizeof(Vector3f), a_Mesh->Vertices.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);
			}

			if (a_Mesh->Normals.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[1]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);

				glBufferData(GL_ARRAY_BUFFER, a_Mesh->Normals.size() * sizeof(Vector3f), a_Mesh->Normals.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);
			}

			if (a_Mesh->TexCoords.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[2]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[2]);

				glBufferData(GL_ARRAY_BUFFER, a_Mesh->TexCoords.size() * sizeof(Vector2f), a_Mesh->TexCoords.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(2);
			}

			if (a_Mesh->Indices.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[3]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOs[3]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Mesh->Indices.size() * sizeof(GLuint), a_Mesh->Indices.data(), GL_STATIC_DRAW);
			}
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			m_Count = a_Mesh->Indices.size();
		}
		
		GLuint GLMesh::GetCount() const
		{
			return m_Count;
		}

		void GLMesh::Bind()
		{
			glBindVertexArray(m_VAO);
		}

		void GLMesh::Unbind()
		{
			glBindVertexArray(0);
		}
	}
}