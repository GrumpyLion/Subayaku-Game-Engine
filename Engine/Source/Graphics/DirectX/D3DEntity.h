#pragma once

#include "Graphics\Interface\IEntity.h"

namespace Graphics
{
	class Material;

	namespace DirectX
	{
		class D3DMesh;
		class D3DMaterial;
		class D3DRenderer;

		class D3DEntity : public IEntity
		{
		private:
			D3DMesh *m_Mesh = nullptr;
			D3DMaterial *m_Material = nullptr;
			D3DRenderer *m_Renderer = nullptr;

			Scene::GameObject *m_Parent = nullptr;

		public:
			~D3DEntity();

			bool Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent) override;
			void Render() override;
		};
	}
}