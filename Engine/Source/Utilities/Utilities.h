#pragma once

#define SHUTDOWN_AND_DELETE(p) if(p!= nullptr) { p->Shutdown(); SafeDelete(p); } 

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include "Core\SEngineContext.h"

template<typename T> void SafeDelete(T*& aInterface)
{
	if (aInterface != nullptr)
	{
		delete aInterface;
		aInterface = nullptr;
	}
}

template<typename T> bool CheckIfPointerIsInvalid(T*& aInterface)
{
	if (aInterface == nullptr)
		return true;

	return false;
}

inline void ErrorBox(LPWSTR a_Text)
{
	MessageBox(nullptr, a_Text, L"Error", MB_OK | MB_ICONERROR);
}

inline void LogErr(std::string a_Format, ...)
{
	va_list v1;
	va_start(v1, a_Format);
	auto ret = vprintf(a_Format.c_str(), v1);
	va_end(v1);
	//printf("Error: %s\n", a_Format);
}

inline void LogWar(std::string a_Text)
{
	printf("Warning: %s\n", a_Text.c_str());
}

inline void Log(const char* a_Text)
{
	printf("%s\n", a_Text);
}

inline std::string GetShaderLocation(Core::SEngineContext &a_Context, std::string a_Path)
{
	std::string location;

	if(a_Context.RDevice == Core::RenderDevice::OpenGL)
		location = "Assets/Shaders/GLSL/";
	else
		location = "Assets/Shaders/HLSL/";

	location.append(a_Path);
	return location;
}

inline std::string GetExtension(std::string a_Path)
{
	int indexOfLastPeriod = (int)a_Path.find_last_of(".");
	return a_Path.substr(indexOfLastPeriod + 1);
}

inline void ToLowerCase(std::string &a_String)
{
	std::transform(a_String.begin(), a_String.end(), a_String.begin(), ::tolower);
}