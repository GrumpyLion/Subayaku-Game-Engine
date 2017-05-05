#pragma once

#include "Graphics\Interface\IRenderFactory.h"
#include "GLTexture.h"
#include "GLMesh.h"

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderFactory : public IRenderFactory
		{
		public:
			GLTexture *CreateTexture(STextureDesc a_Desc) override;
			IMesh *CreateMesh(SMeshDesc a_Desc) override;
		};
	}
}