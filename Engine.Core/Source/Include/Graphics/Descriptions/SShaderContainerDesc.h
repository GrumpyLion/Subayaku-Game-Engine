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

		bool operator==(const SShaderContainerDesc& a_Other) const
		{
			return (Vertex == a_Other.Vertex &&
					Fragment == a_Other.Fragment);
		}
	};
}

// Added for std::unordered_map
//

namespace std
{
	template<>
	struct hash<Graphics::SShaderContainerDesc>
	{
		std::size_t operator()(const Graphics::SShaderContainerDesc& k) const
		{
			size_t result = 17;

			result += 31 + hash<std::string>()(k.Vertex.FilePath);
			result += 31 + hash<std::string>()(k.Fragment.FilePath);

			return result;
		}
	};
}