#pragma once

#include "Graphics\Descriptions\SEntityDesc.h"

namespace Graphics
{
	class IRenderer;

	class IEntity
	{
	public:
		
		virtual ~IEntity() { }
		
		virtual	bool Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer) = 0;

		virtual void Render() = 0;

		//virtual void SetBuffer() = 0;
	};
}