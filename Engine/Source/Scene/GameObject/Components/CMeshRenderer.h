#pragma once

#include "Interface\IComponent.h"

namespace Graphics
{
	class Mesh;
	class Material;
}

namespace Scene
{
	class CMeshRenderer : public IComponent
	{
	private:
		Graphics::Mesh *m_Mesh = nullptr;
		Graphics::Material *m_Material = nullptr;

	public:
		bool Initialize(GameObject *a_Parent) override;
		void Update() override;
		void Shutdown() override;

		Graphics::Mesh *GetMesh();
		Graphics::Material *GetMaterial();
	};
}