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
		std::string FilePath;
	};
}