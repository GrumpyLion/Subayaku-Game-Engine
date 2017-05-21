#pragma once

#include "Interface\IComponent.h"
#include "Graphics\Cache\SMeshDesc.h"
#include "Scene\GameObject\GameObject.h"
#include "Graphics\Material.h"

#include <memory>

namespace Graphics
{
	class Mesh;
}

namespace Scene
{
	class CMeshRenderer : public IComponent
	{
	protected:
		Graphics::SMeshDesc m_Mesh {};
		std::unique_ptr<Graphics::Material> m_Material = nullptr;

	public:
		~CMeshRenderer();

		virtual bool Initialize(GameObject *a_Parent, const char* a_ModelLocation, std::unique_ptr<Graphics::Material> a_Material);
		virtual bool Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, std::unique_ptr<Graphics::Material> a_Material);
		virtual void Update() override;

		Graphics::SMeshDesc &GetMesh();
		Graphics::Material *GetMaterial();
	};
}