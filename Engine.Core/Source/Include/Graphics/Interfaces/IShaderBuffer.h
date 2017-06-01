#pragma once

#include "Graphics\Descriptions\SShaderBufferDesc.h"
#include "Graphics\Interfaces\IRenderer.h"

namespace Graphics
{
	class IShaderBuffer
	{
	public:
		virtual ~IShaderBuffer() { }

		virtual bool Initialize(SShaderBufferDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}