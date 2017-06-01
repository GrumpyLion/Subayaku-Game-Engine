#pragma once

#include "Graphics\Descriptions\STextureDesc.h"
#include "Graphics\Interfaces\IRenderer.h"

namespace Graphics
{
	class ITexture
	{
	public:
		std::string UniformName;

		virtual ~ITexture() {}
		virtual bool Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}