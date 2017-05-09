#pragma once

#include <string>

namespace Graphics
{
	struct SShaderBufferDesc
	{
		std::string BufferName = "Unnamed";
		unsigned short BufferSize;
		unsigned short BufferIndex;
		bool IsDynamic = false;
	};
}