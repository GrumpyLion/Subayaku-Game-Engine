#pragma once

#include "Interface\IComponent.h"
#include "Graphics\Cache\SMeshDesc.h"

namespace Graphics
{
	class Mesh;
	class Material;
}

namespace Scene
{
	class CMeshRenderer : public IComponent
	{
	protected:
		Graphics::SMeshDesc m_Mesh {};
		Graphics::Material *m_Material = nullptr;

	public:
		virtual bool Initialize(GameObject *a_Parent, const char* a_ModelLocation, Graphics::Material *a_Material);
		virtual void Update();
		void Shutdown();

		Graphics::SMeshDesc &GetMesh();
		Graphics::Material *GetMaterial();
	};
}