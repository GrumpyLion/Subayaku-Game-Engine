#pragma once

#include <vector>
#include "Math\Math.h"
#include "Graphics\MeshInfo.h"

namespace Graphics
{
	class Mesh
	{
	public:
		std::vector<Vector3f> Vertices;
		std::vector<Vector3f> Normals;
		std::vector<Vector2f> TexCoords;
		std::vector<unsigned int> Indices;

		EMeshPrimitive Mode;
		bool ShouldCull = true;
		bool HasIndices = false;
	};
}