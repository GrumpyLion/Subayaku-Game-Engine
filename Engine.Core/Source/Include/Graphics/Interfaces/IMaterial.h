#pragma once

#include "Graphics\Material.h"

namespace Graphics
{
	class IRenderer;

	class IMaterial
	{
	public:
		virtual bool Initialize(Material *a_Material, IRenderer *a_Renderer) = 0;

		virtual bool Bind() = 0;
	};
}