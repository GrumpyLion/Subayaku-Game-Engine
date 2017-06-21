#pragma once

#include <string>
#include <unordered_map>

#include "Graphics\Descriptions\SShaderContainerDesc.h"
#include "Graphics\Descriptions\STextureDesc.h"
#include "Graphics\Enums\TextureEnums.h"

#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	class ITexture;

	class Material
	{		
	public:
		Scene::Transformation *ParentTransform = nullptr;

		std::unordered_map<std::string, STextureDesc> Textures;
		Graphics::SShaderContainerDesc Shaders{};
		ETextureFilter TextureFilter = ETextureFilter::NEAREST;

		void AddShader(std::string a_FilePath);
		void AddTexture(STextureDesc &a_TextureInfo);
		void RemoveTexture(std::string a_FileName);

		bool operator==(const Material& a_Other) const
		{
			// If the size is not the same well then bye :D
			if (Textures.size() > 0 && Textures.size() != a_Other.Textures.size())
				return false;

			for (auto &temp : Textures)
			{
				bool found = false;

				for (auto &temp2 : a_Other.Textures)
				{
					if (temp.second.FilePath == temp2.second.FilePath)
					{
						found = true;
						break;
					}
				}
				if (!found)
					return false;
			}

			return (TextureFilter == a_Other.TextureFilter &&
					Shaders == a_Other.Shaders);
		}

	};

}

// Added for std::unordered_map
//

namespace std
{
	template<>
	struct hash<Graphics::Material>
	{
		std::size_t operator()(const Graphics::Material& k) const
		{
			size_t result = 17;

			if(k.Textures.size() > 0)
				for(auto &temp : k.Textures)
					result += 31 + hash<Graphics::STextureDesc>()(temp.second);

			result += 31 + hash<Graphics::SShaderContainerDesc>()(k.Shaders);
			result += 31 + hash<Graphics::ETextureFilter>()(k.TextureFilter);

			return result;
		}
	};
}