#pragma once

#include <vector>

namespace Graphics
{
	class Mesh
	{
	public:
		std::vector<float> Vertices;
		std::vector<float> Normals;
		std::vector<float> TexCoords;
		std::vector<unsigned int> Indices;
	};
}