#pragma once

#include <vector>
#include "Math\Math.h"

bool loadAssimp(
	const char * path,
	std::vector<unsigned int> & indices,
	std::vector<Vector3f> & vertices,
	std::vector<Vector2f> & uvs,
	std::vector<Vector3f> & normals
);
