#pragma once

#include "Graphics\Descriptions\SShaderDesc.h"

namespace Graphics
{
	class IRenderer;

	class IShader
	{
	public:
		virtual ~IShader() {}
		virtual bool Initialize(SShaderDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}