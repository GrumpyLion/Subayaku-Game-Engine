#pragma once

#include "Interface\IComponent.h"
#include "Graphics\Descriptions\SMeshDesc.h"
#include "Graphics\Descriptions\SEntityDesc.h"

#include "Graphics\Material.h"

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
		Graphics::Material m_Material{};
		Graphics::SEntityDesc m_Entity{};

	public:
		~CMeshRenderer();

		//I now want to load everything on the engine side. So i can decouple the graphics side.
		void InitializeEntity();

		virtual bool Initialize(GameObject *a_Parent, std::string a_ModelLocation, Graphics::Material &a_Material);
		virtual bool Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, Graphics::Material &a_Material);

		virtual void Update() override;
	
		void SetMaterial(Graphics::Material &a_Material);
		Graphics::Material& GetMaterial();
	};
}