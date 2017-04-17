#pragma once

#include <Windows.h>

namespace Core
{
	enum RenderDevice
	{
		OpenGL,
		DirectX
	};

	struct SEngineContext
	{
		RenderDevice RDevice = RenderDevice::OpenGL;
		LPCWSTR Title = L"Subayaku ^-^";
		int Width = 1024, Height = 600;
		bool IsFullScreen = false;
	};
}