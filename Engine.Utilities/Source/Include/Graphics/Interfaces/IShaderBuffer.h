#pragma once

#include "Graphics\Descriptions\SShaderBufferDesc.h"

namespace Graphics
{
	class IRenderer;

	class IShaderBuffer
	{
	public:
		virtual ~IShaderBuffer() { }

		virtual bool Initialize(SShaderBufferDesc &a_Desc, IRenderer *a_Renderer) = 0;
	};
}