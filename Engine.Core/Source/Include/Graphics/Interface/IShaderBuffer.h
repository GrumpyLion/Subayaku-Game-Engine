#pragma once

#include "Graphics\Cache\SShaderBufferDesc.h"
#include "IRenderer.h"

namespace Graphics
{
	class IShaderBuffer
	{
	public:
		virtual ~IShaderBuffer() { }

		virtual bool Initialize(SShaderBufferDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}