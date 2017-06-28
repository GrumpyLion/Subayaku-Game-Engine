#pragma once

#include <vector>
#include <string>
#include "Math\Math.h"
#include "Graphics\Enums\MeshEnums.h"

namespace Graphics
{
	struct SMeshDesc
	{
		std::vector<Vector3f> Vertices;
		std::vector<Vector3f> Normals;
		std::vector<Vector3f> Tangents;
		std::vector<Vector3f> Bitangents;
		std::vector<Vector2f> TexCoords;
		std::vector<unsigned int> Indices;

		EMeshPrimitive Mode;

		bool ShouldCull = true;
		bool HasIndices = true;
		bool NeedsToBeLoaded = false;
		std::string FilePath;

		bool operator==(const SMeshDesc& a_Other) const
		{
			return (Vertices.size() == a_Other.Vertices.size() &&
					Normals.size() == a_Other.Normals.size() &&
					Tangents.size() == a_Other.Tangents.size() &&
					Bitangents.size() == a_Other.Bitangents.size() &&
					TexCoords.size() == a_Other.TexCoords.size() &&
					Indices.size() == a_Other.Indices.size() &&
					FilePath == a_Other.FilePath &&
					ShouldCull == a_Other.ShouldCull &&
					HasIndices == a_Other.HasIndices);
		}
	};
}

// Added for std::unordered_map
//

namespace std
{
	template<>
	struct hash<Graphics::SMeshDesc>
	{
		std::size_t operator()(const Graphics::SMeshDesc& k) const
		{
			size_t result = 17;

			result += 31 + hash<size_t>()(k.Vertices.size());
			result += 31 + hash<size_t>()(k.Normals.size());
			result += 31 + hash<size_t>()(k.Tangents.size());
			result += 31 + hash<size_t>()(k.TexCoords.size());
			result += 31 + hash<size_t>()(k.Bitangents.size());
			result += 31 + hash<size_t>()(k.Bitangents.size());
			result += 31 + hash<std::string>()(k.FilePath);

			return result;
		}
	};
}