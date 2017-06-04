#pragma once

namespace Graphics
{
	enum EMeshPrimitive
	{
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		LINES,
		POINTS
	};

	enum ECullFace
	{
		FRONT,
		BACK,
		FRONT_AND_BACK
	};
}