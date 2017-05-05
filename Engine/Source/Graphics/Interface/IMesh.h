#pragma once

#include "Graphics\Cache\SMeshDesc.h"

namespace Graphics
{
	class IMesh
	{
	public:
		virtual ~IMesh() { }

		virtual void Initialize(SMeshDesc &a_Desc) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetCount() = 0;
	};
}