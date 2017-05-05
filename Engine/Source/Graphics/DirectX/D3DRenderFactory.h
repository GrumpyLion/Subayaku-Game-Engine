#pragma once

#include "Graphics\Interface\IRenderFactory.h"
#include "D3DMesh.h"

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderFactory : public IRenderFactory
		{
		public:
			ITexture *CreateTexture(STextureDesc a_Desc) override;
			D3DMesh *CreateMesh(SMeshDesc a_Desc) override;
		};
	}
}