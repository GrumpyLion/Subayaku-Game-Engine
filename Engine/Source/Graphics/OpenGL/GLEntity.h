#pragma once

#include <vector>

namespace Graphics
{
	class Material;
	class Mesh;

	namespace OpenGL
	{
		class GLMesh;
		class GLMaterial;

		class GLEntity
		{
		private:
			GLMesh *m_Mesh = nullptr;
			GLMaterial *m_Material = nullptr;

		public:
			~GLEntity();

			bool Initialize(Mesh *a_Mesh, Material *a_Material);
			void Render();

		};
	}
}