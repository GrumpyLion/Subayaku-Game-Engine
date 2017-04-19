#pragma once

#include <vector>
#include "Math\Math.h"

namespace Graphics
{
	class Mesh
	{
	public:
		std::vector<Vector3f> Vertices;
		std::vector<Vector3f> Normals;
		std::vector<Vector2f> TexCoords;
		std::vector<unsigned int> Indices;
	};
}