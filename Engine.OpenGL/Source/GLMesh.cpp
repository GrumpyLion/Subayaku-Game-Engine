#include "OpenGL\GLMesh.h"
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

		bool GLMesh::Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer)
		{			
			ShouldCull = a_Desc.ShouldCull;
			Mode = a_Desc.Mode;

			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			for (int i = 0; i < numVBOs; i++)
				m_VBOs[i] = 0;

			if (a_Desc.Vertices.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[0]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);

				glBufferData(GL_ARRAY_BUFFER, a_Desc.Vertices.size() * sizeof(Vector3f), a_Desc.Vertices.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);
			}

			if (a_Desc.Normals.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[1]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);

				glBufferData(GL_ARRAY_BUFFER, a_Desc.Normals.size() * sizeof(Vector3f), a_Desc.Normals.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);
			}

			if (a_Desc.Normals.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[1]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);

				glBufferData(GL_ARRAY_BUFFER, a_Desc.Normals.size() * sizeof(Vector3f), a_Desc.Normals.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);
			}

			if (a_Desc.TexCoords.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[2]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[2]);

				glBufferData(GL_ARRAY_BUFFER, a_Desc.TexCoords.size() * sizeof(Vector2f), a_Desc.TexCoords.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(2);
			}

			if (a_Desc.Tangents.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[3]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[3]);

				glBufferData(GL_ARRAY_BUFFER, a_Desc.Tangents.size() * sizeof(Vector3f), a_Desc.Tangents.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(3);
			}

			if (a_Desc.Bitangents.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[4]);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[4]);

				glBufferData(GL_ARRAY_BUFFER, a_Desc.Bitangents.size() * sizeof(Vector3f), a_Desc.Bitangents.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(4);
			}

			if (a_Desc.Indices.size() > 0)
			{
				glGenBuffers(1, &m_VBOs[5]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOs[5]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Desc.Indices.size() * sizeof(GLuint), a_Desc.Indices.data(), GL_STATIC_DRAW);
			}
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			HasIndices = a_Desc.HasIndices;
			if (a_Desc.HasIndices)
			{
				m_Count = (GLuint)a_Desc.Indices.size();
			}
			else
			{
				m_Count = (GLuint)a_Desc.Vertices.size();
			}

			return true;
		}
		
		GLuint GLMesh::GetCount()
		{
			return m_Count;
		}

		void GLMesh::Bind()
		{
			glBindVertexArray(m_VAO);
			if (!ShouldCull)
				glDisable(GL_CULL_FACE);
		}

		void GLMesh::Unbind()
		{
			glBindVertexArray(0);
			if (!ShouldCull)
				glEnable(GL_CULL_FACE);
		}
	}
}