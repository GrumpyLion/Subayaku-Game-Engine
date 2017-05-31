#pragma once

#include "IRenderer.h"
#include "Graphics\Material.h"

namespace Graphics
{
	class IMaterial
	{
	public:
		virtual bool Initialize(Material *a_Material, IRenderer *a_Renderer) = 0;

		virtual void Bind() = 0;
	};
}