#pragma once

#include "Graphics\Interface\IEntity.h"
#include "D3DMaterial.h"
#include <memory>

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
			bool Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent) override;
			void Render() override;
		};
	}
}