#pragma once

#include "Interface\IComponent.h"
#include "Graphics\Descriptions\SMeshDesc.h"

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
		Graphics::SMeshDesc m_Mesh{};

		std::unique_ptr<Graphics::Material> m_Material = nullptr;

	public:
		~CMeshRenderer();

		//I now want to load everything on the engine side. So i can decouple the graphics side.
		void InitializeEntity();

		virtual bool Initialize(GameObject *a_Parent, const char* a_ModelLocation, std::unique_ptr<Graphics::Material> a_Material);
		virtual bool Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, std::unique_ptr<Graphics::Material> a_Material);
		virtual void Update() override;
	
		//Graphics::SEntityDesc &GetEntityDesc();
	};
}