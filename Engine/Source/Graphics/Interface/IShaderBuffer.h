#pragma once

#include "Graphics\Cache\SShaderBufferDesc.h"

namespace Graphics
{
	class IShaderBuffer
	{
	public:
		virtual ~IShaderBuffer() { }

		virtual bool Initialize(SShaderBufferDesc a_Desc) = 0;
	};
}