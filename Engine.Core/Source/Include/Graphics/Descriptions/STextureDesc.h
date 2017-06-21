#pragma once

#include "Graphics\Enums\TextureEnums.h"
#include <string>
#include <vector>

namespace Graphics
{
	struct STextureDesc
	{
		ETextureFilter Filter;
		ETextureFormat Format;

		std::string FilePath = "";
		
		int RegisterIndex = 0;
		const char* UniformName = "";

		std::vector<unsigned char> PixelData;

		int Width = 0;
		int Height = 0;

		bool operator==(const STextureDesc& a_Other) const
		{
			return (Filter == a_Other.Filter &&
					Format == a_Other.Format &&
					FilePath == a_Other.FilePath &&
					RegisterIndex == a_Other.RegisterIndex &&
					UniformName == a_Other.UniformName && 
					Width == a_Other.Width &&
					Height == a_Other.Height);
		}
	};
}

// Added for std::unordered_map
//

namespace std
{
	template<>
	struct hash<Graphics::STextureDesc>
	{
		std::size_t operator()(const Graphics::STextureDesc& k) const
		{
			size_t result = 17;

			result += 31 + hash<Graphics::ETextureFilter>()(k.Filter);
			result += 31 + hash<Graphics::ETextureFormat>()(k.Format);

			result += 31 + hash<std::string>()(k.FilePath);
			result += 31 + hash<std::string>()(k.UniformName);
			result += 31 + hash<int>()(k.RegisterIndex);

			result += 31 + hash<int>()(k.Width);
			result += 31 + hash<int>()(k.Height);

			return result;
		}
	};
}