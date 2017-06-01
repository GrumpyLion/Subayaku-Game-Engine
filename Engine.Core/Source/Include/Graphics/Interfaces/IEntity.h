#pragma once

#include "Graphics\Descriptions\SEntityDesc.h"
#include "Graphics\Material.h"
#include "Scene\GameObject\GameObject.h"

#include "IRenderer.h"
#include "IShaderBuffer.h"

namespace Graphics
{
	class IEntity
	{
	public:
		
		virtual ~IEntity() { }
		
		virtual	bool Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer) = 0;

		virtual void Render() = 0;

		//virtual void SetBuffer() = 0;
	};
}