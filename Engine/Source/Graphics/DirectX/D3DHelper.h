#pragma once

#include <Windows.h>
#include <d3d11.h>
#include "Graphics\Cache\TextureEnums.h"
#include "Graphics\Cache\STextureDesc.h"
#include "Graphics\Cache\SMeshDesc.h"

namespace Graphics
{
	namespace DirectX
	{
		template<typename T> inline void SafeRelease(T*& aInterface)
		{
			if (aInterface != nullptr)
			{
				aInterface->Release();
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

		inline D3D11_FILTER ETextureFilterToDX(ETextureFilter &a_Format)
		{
			D3D11_FILTER format;

			switch (a_Format)
			{
			case ETextureFilter::LINEAR:
				format = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				break;

			case ETextureFilter::NEAREST:
				format = D3D11_FILTER_MIN_MAG_MIP_POINT;
				break;
			}

			return format;
		}

		inline DXGI_FORMAT ETextureFormatToDX(ETextureFormat &a_Format)
		{
			DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

			switch (a_Format)
			{
			case ETextureFormat::RGBA:
				format = DXGI_FORMAT_R8G8B8A8_UNORM;
				break;

			//case ETextureFormat::RGB:
			//	format = DXGI_FORMAT_R8G8B8A8_UNORM;
			//	break;

			//case ETextureFormat::RG:
			//	format = DXGI_FORMAT_R32G32_FLOAT;
			//	break;

			//case ETextureFormat::R:
			//	format = DXGI_FORMAT_R8_UNORM;
			//	break;

			case ETextureFormat::BGRA:
				format = DXGI_FORMAT_B8G8R8A8_UNORM;
				break;

			default:
				break;
			}

			return format;
		}
	}
}