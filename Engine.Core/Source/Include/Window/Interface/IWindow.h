#pragma once

#include "Core\SEngineContext.h"

namespace Core
{
	class IWindow
	{
	public:
		virtual ~IWindow() {}

		virtual bool Initialize(SEngineContext &a_EngineContext) = 0;
		virtual bool Update() = 0;

	};
}