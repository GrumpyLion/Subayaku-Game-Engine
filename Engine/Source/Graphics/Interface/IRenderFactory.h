#pragma once

#include "Graphics\Cache\STextureDesc.h"
#include "Graphics\Cache\SMeshDesc.h"
#include "ITexture.h"
#include "IMesh.h"

namespace Graphics
{
	class IRenderFactory
	{
	public:
		virtual ITexture *CreateTexture(STextureDesc a_Desc) = 0;
		virtual IMesh *CreateMesh(SMeshDesc a_Desc) = 0;
	};
	
}