#pragma once

#include "EEvents.h"

namespace Core
{
	struct SEventDesc
	{
		EEvents Event = EEvents::UNDEFINED;
		void* Description = nullptr;
	};
}