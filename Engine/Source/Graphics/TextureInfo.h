#pragma once

#include "Cache\TextureEnums.h"

namespace Graphics
{
	struct TextureInfo
	{
		const char* UniformName;
		ETextureFilter Filter;
	};
}