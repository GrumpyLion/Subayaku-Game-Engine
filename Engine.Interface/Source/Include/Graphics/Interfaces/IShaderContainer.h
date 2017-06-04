#pragma once

#include "Graphics\Descriptions\SShaderContainerDesc.h"
#include "Math\Math.h"

namespace Graphics
{
	class IRenderer;

	class IShaderContainer
	{
	public:
		virtual ~IShaderContainer() {}

		virtual bool Initialize(SShaderContainerDesc &a_Desc, IRenderer *a_Renderer) = 0;

		virtual void BindProgram() = 0;
		virtual void UnbindProgram() = 0;
		virtual bool GetError() = 0;
	};
}