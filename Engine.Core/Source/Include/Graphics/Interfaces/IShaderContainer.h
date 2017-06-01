#pragma once

#include "Graphics\Descriptions\SShaderContainerDesc.h"
#include "Graphics\Interfaces\IRenderer.h"
#include "Math\Math.h"

namespace Graphics
{
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