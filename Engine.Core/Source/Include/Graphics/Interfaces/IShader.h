#pragma once

#include "Graphics\Descriptions\SShaderDesc.h"
#include "Graphics\Interfaces\IRenderer.h"

namespace Graphics
{
	class IShader
	{
	public:
		virtual ~IShader() {}
		virtual bool Initialize(SShaderDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}