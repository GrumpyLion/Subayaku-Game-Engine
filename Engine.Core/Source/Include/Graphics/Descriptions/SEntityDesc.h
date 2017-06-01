#pragma once

#include "Graphics\Material.h"
#include "Graphics\Descriptions\SMeshDesc.h"

namespace Graphics
{
	struct SEntityDesc
	{
		SMeshDesc Mesh{};
		Material* Material = nullptr;
	};
}