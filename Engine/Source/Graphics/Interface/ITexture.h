#pragma once

#include "Graphics\Cache\STextureDesc.h"

namespace Graphics
{
	class ITexture
	{
	public:
		virtual ~ITexture() {}
		virtual bool Initialize(STextureDesc a_Desc) = 0;
	};
}