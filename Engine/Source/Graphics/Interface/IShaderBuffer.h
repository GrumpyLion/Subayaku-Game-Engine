#pragma once

#include "Graphics\Interface\SShaderBufferDesc.h"

namespace Graphics
{
	class IShaderBuffer
	{
	public:
		virtual ~IShaderBuffer() { }

		virtual bool Initialize(SShaderBufferDesc a_Desc) = 0;
	};
}