#pragma once

#include <string>
#include "SShaderDesc.h"

namespace Graphics
{
	struct SShaderContainerDesc
	{
		SShaderDesc Vertex{};
		SShaderDesc Fragment{};
		std::string ShaderContainerName;
	};
}