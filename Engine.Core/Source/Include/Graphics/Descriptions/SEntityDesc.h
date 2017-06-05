#pragma once

#include "Graphics\Material.h"
#include "Graphics\Descriptions\SMeshDesc.h"

namespace Scene
{
	class CMeshRenderer;
	class GameObject;
}

namespace Graphics
{
	struct SEntityDesc
	{
		SMeshDesc Mesh{};
		Material* Material = nullptr;
		
		Scene::CMeshRenderer *MeshRenderer = nullptr;
		Scene::GameObject *Parent = nullptr;
	};
}