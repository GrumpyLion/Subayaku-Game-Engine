#pragma once

#include "Math\Math.h"

namespace Scene
{
	class Transformation
	{
	public:
		Transformation()
		{

		}

		Vector3f Position;
		Vector3f Scale = Vector3f(1,1,1);
		Vector3f Rotation;
	};
}