#pragma once

#include <Windows.h>
#include <string>

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
		std::string PathToPak = "Assets.paklol";
		LPCWSTR Title = L"Subayaku";

		int AdjustedWidth, AdjustedHeight;
		int Width = 1024, Height = 600;
		
		int xPos = 0, yPos = 0;
		bool IsFullScreen = false;
	};
}