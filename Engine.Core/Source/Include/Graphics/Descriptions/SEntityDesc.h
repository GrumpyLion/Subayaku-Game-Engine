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
		Matrix4f *Transform = nullptr;

		bool operator==(const SEntityDesc& a_Other) const
		{
			if(Material != nullptr)
				return (Mesh == a_Other.Mesh &&
					*Material == *a_Other.Material);

			return (Mesh == a_Other.Mesh);
		}
	};
}

// Added for std::unordered_map
//

namespace std
{
	template<>
	struct hash<Graphics::SEntityDesc>
	{
		std::size_t operator()(const Graphics::SEntityDesc& k) const
		{
			size_t result = 17;

			result += 31 + hash<Graphics::SMeshDesc>()(k.Mesh);
			
			if(k.Material != nullptr)
				result += 31 + hash<Graphics::Material>()(*k.Material);

			return result;
		}
	};
}