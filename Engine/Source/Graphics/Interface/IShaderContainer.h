#pragma once

#include "Graphics\Material.h"
#include "Math\Math.h"

namespace Graphics
{
	class IShaderContainer
	{
	public:
		virtual ~IShaderContainer() {}

		virtual bool Initialize(Material *a_Material) = 0;

		virtual void BindProgram() = 0;
		virtual void UnbindProgram() = 0;
		virtual bool GetError() = 0;
	};
}