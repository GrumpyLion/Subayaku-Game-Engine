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

		bool m_Removed = false;

	public:
		// Cleanup 
		//
		~CMeshRenderer();

		// Initialzes an Entity Description and fires an event
		//
		void InitializeEntity();

		// Loads an model from memory
		//
		virtual bool Initialize(GameObject *a_Parent, std::string a_ModelLocation, Graphics::Material &a_Material);
		
		// You can load it yourself or create an primitive
		//
		virtual bool Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, Graphics::Material &a_Material);

		// Empty
		virtual void Update() override;
		
		// Fires an Event for deletion
		//
		void Remove();

		void SetMaterial(Graphics::Material &a_Material) { m_Material = a_Material; };
		Graphics::Material& GetMaterial() { return m_Material; };
	};
}