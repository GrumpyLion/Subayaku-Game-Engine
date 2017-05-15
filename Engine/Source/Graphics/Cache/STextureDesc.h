#pragma once

#include "TextureEnums.h"
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

		std::vector<std::uint8_t> PixelData;

		int Width = 0;
		int Height = 0;
	};
}