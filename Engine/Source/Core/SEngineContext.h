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
		LPCWSTR Title = L"Subayaku";

		int AdjustedWidth, AdjustedHeight;
		int Width = 1024, Height = 600;
		
		int xPos = 0, yPos = 0;
		bool IsFullScreen = false;
	};
}