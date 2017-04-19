#pragma once

#include <vector>

namespace Scene
{
	class GameObject;
}

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
			Scene::GameObject *m_Parent = nullptr;

		public:
			~GLEntity();

			bool Initialize(Mesh *a_Mesh, Material *a_Material, Scene::GameObject *a_Parent);
			void Render();

		};
	}
}