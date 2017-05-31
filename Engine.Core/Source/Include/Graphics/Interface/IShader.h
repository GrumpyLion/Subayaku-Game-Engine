#pragma once

#include "Graphics\Cache\SShaderDesc.h"
#include "IRenderer.h"

namespace Graphics
{
	class IShader
	{
	public:
		virtual ~IShader() {}
		virtual bool Initialize(SShaderDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}