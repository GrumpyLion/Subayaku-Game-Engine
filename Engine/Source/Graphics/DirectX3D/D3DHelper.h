#pragma once

#include <Windows.h>

namespace Graphics
{
	namespace DirectX
	{
		template<typename T> void NSafeRelease(T*& aInterface)
		{
			if (aInterface != nullptr)
			{
				aInterface->Release();
				aInterface = nullptr;
			}
		}

		template<typename T> void NSafeDelete(T*& aInterface)
		{
			if (aInterface != nullptr)
			{
				delete aInterface;
				aInterface = nullptr;
			}
		}
	}
}