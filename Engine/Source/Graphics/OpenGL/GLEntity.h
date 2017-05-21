#pragma once

#include "Graphics\Cache\SMeshDesc.h"
#include "Graphics\Interface\IEntity.h"

#include "GLMaterial.h"

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

		class GLEntity : public IEntity
		{
		private:
			GLMesh* m_Mesh = nullptr;

			std::unique_ptr<GLMaterial> m_Material = nullptr;

			//Observable pointer
			Scene::GameObject *m_Parent = nullptr;

		public:
			~GLEntity()
			{			}

			bool Initialize(SMeshDesc &a_Mesh, Material* a_Material, Scene::GameObject *a_Parent) override;
			void Render() override;

		};
	}
}