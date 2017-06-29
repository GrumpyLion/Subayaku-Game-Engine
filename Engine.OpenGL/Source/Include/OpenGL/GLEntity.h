#pragma once

#include "Graphics\Interfaces\IEntity.h"
#include "GLMaterial.h"
#include "GLMesh.h"
#include <vector>

namespace Scene
{
	class GameObject;
	class CMeshRenderer;
}

namespace Graphics
{
	class Material;

	namespace OpenGL
	{
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
			__declspec(dllexport) void AddInstance(Matrix4f *a_MeshRenderer) final;
			__declspec(dllexport) void RemoveInstance(Matrix4f *a_MeshRenderer) final;
			__declspec(dllexport) size_t GetInstanceCount() final { return m_Mesh->GetInstanceCount(); }
 
		};
	}
}