#pragma once

#include "Graphics\Interfaces\IEntity.h"
#include "D3DMaterial.h"
#include <memory>

namespace Scene
{
	class CMeshRenderer;
}

namespace Graphics
{
	class Material;

	namespace DirectX
	{
		class D3DMesh;
		class D3DRenderer;

		class D3DEntity : public IEntity
		{
		private:
			//Observable Pointers
			D3DMesh *m_Mesh = nullptr;
			D3DRenderer *m_Renderer = nullptr;
			Scene::GameObject *m_Parent = nullptr;

			std::unique_ptr<D3DMaterial> m_Material;

			bool HasIndices = true;
		public:
			__declspec(dllexport) bool Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer) final;
			__declspec(dllexport) void Render() final;
			__declspec(dllexport) void AddInstance(Matrix4f *a_MeshRenderer) final;
			__declspec(dllexport) void RemoveInstance(Matrix4f *a_MeshRenderer) final;
			__declspec(dllexport) size_t GetInstanceCount() final { return 0; }
		};
	}
}