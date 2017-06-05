#pragma once

#include "Graphics\Descriptions\STextureDesc.h"

namespace Graphics
{
	class IRenderer;

	class ITexture
	{
	public:
		std::string UniformName;

		virtual ~ITexture() {}
		virtual bool Initialize(STextureDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}