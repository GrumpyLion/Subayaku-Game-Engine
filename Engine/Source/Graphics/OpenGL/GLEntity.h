#pragma once

#include <vector>
#include "Graphics\Cache\SMeshDesc.h"

namespace Scene
{
	class GameObject;
}

namespace Graphics
{
	class Material;

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
			bool m_IsPrimitive = false;

		public:
			~GLEntity();

			bool Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent);
			void Render();

		};
	}
}