#pragma once

#include "Graphics\Cache\SShaderDesc.h"

namespace Graphics
{
	class IShader
	{
	public:
		virtual ~IShader() {}
		virtual bool Initialize(SShaderDesc &a_Desc) = 0;
	};
}