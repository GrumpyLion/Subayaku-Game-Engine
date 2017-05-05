#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Interface\IMesh.h"

namespace Graphics
{
	namespace OpenGL
	{
		const int numVBOs = 6;

		class GLMesh : public IMesh
		{
		private:
			GLuint m_VAO = 0;
			GLuint m_VBOs[numVBOs];
			GLuint m_Count = 0;

		public:
			bool ShouldCull = true;
			bool HasIndices = true;
			EMeshPrimitive Mode;

			~GLMesh();
			void Initialize(SMeshDesc &a_Desc) override;
			void Bind() override;
			void Unbind() override;
			GLuint GetCount() override;
		};
	}
}