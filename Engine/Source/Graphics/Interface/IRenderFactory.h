#pragma once

#include "Graphics\Cache\STextureDesc.h"
#include "Graphics\Cache\SMeshDesc.h"
#include "Graphics\Cache\SShaderDesc.h"
#include "Graphics\Cache\SShaderBufferDesc.h"

#include "ITexture.h"
#include "IMesh.h"
#include "IShader.h"
#include "IShaderBuffer.h"

#include <memory>

namespace Graphics
{
	class IRenderFactory
	{
	public:
		virtual std::unique_ptr<ITexture> CreateTexture(STextureDesc a_Desc) = 0;
		virtual std::unique_ptr<IMesh> CreateMesh(SMeshDesc a_Desc) = 0;
		virtual std::unique_ptr<IShader> CreateShader(SShaderDesc a_Desc) = 0;
		virtual std::unique_ptr<IShaderBuffer> CreateShaderBuffer(SShaderBufferDesc a_Desc) = 0;
	};
	
}