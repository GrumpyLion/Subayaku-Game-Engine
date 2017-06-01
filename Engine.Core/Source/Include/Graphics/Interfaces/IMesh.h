#pragma once

#include "Graphics\Descriptions\SMeshDesc.h"
#include "Graphics\Interfaces\IRenderer.h"

namespace Graphics
{
	class IMesh
	{
	public:
		virtual ~IMesh() { }

		virtual bool Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetCount() = 0;
	};
}