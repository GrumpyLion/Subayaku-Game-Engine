#pragma once

#include "Graphics\Interface\IRenderFactory.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderFactory : public IRenderFactory
		{
		public:
			std::unique_ptr<ITexture> CreateTexture(STextureDesc a_Desc) override;
			std::unique_ptr<IMesh> CreateMesh(SMeshDesc a_Desc) override;
			std::unique_ptr<IShader> CreateShader(SShaderDesc a_Desc) override;
			std::unique_ptr<IShaderBuffer> CreateShaderBuffer(SShaderBufferDesc a_Desc) override;
		};
	}
}