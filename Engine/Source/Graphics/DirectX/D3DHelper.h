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

		inline bool Failed(HRESULT aResult)
		{
			if (FAILED(aResult))
			{
				LPTSTR buffer;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)aResult, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

				MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR);
				LocalFree(buffer);
				return true;
			}
			return false;
		}
	}
}