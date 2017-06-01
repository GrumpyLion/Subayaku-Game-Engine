#pragma once

#include "Graphics\Interfaces\IEntity.h"
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
		class GLRenderer;

		class GLEntity : public IEntity
		{
		private:
			GLMesh* m_Mesh = nullptr;
			GLRenderer *m_Renderer = nullptr;

			std::unique_ptr<GLMaterial> m_Material = nullptr;

		public:
			~GLEntity()
			{			}

			__declspec(dllexport) bool Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer) final;
			__declspec(dllexport) void Render() final;

		};
	}
}