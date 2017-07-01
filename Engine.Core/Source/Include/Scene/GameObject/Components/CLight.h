#pragma once

#include "Interface\IComponent.h"
#include "Math\Math.h"

namespace Scene
{
	class CLight : public IComponent
	{
	private:
		// If the w component is 1.0 it's a position if 0.0 it's a direction
		//
		Vector4f Position;

		Vector4f Color;

	public:
		CLight();

	};
}