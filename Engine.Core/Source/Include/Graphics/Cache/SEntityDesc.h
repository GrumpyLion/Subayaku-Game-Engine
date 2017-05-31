#pragma once

#include "Graphics\Material.h"
#include "Graphics\Cache\SMeshDesc.h"

namespace Graphics
{
	struct SEntityDesc
	{
		SMeshDesc Mesh{};
		Material* Material = nullptr;
	};
}