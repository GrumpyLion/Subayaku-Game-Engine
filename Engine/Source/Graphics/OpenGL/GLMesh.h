#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Mesh.h"

namespace Graphics
{

	namespace OpenGL
	{
		const int numVBOs = 4;

		class GLMesh : public Mesh
		{
		private:
			GLuint m_VAO = 0;
			GLuint m_VBOs[numVBOs];
			GLuint m_Count = 0;

		public:
			~GLMesh();
			void Initialize(Mesh *a_Mesh);
			void Bind();
			void Unbind();
			GLuint GetCount() const;
		};
	}
}