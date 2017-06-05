#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <memory>
#include "Core\SEngineContext.h"

#define DLLEXPORT __declspec(dllexport) 

template<typename TO, typename FROM> 
std::unique_ptr<TO> static_cast_uptr(std::unique_ptr<FROM>&& old)
{
	return std::unique_ptr<TO>{static_cast<TO*>(old.release())};
	//conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}

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

#define LogErr(format, ...) NLogErr(__FUNCTION__, format, __VA_ARGS__)
#define LogFunction (format, ...) _Log(__FUNCTION__, format, __VA_ARGS__)

template<typename...Args>
inline void _Log(const std::string& func, const std::string& format, Args&&...args)
{
	printf("%s ", func.c_str());
	printf(format.c_str(), std::forward<Args>(args)...);
	printf("\n");
}

template<typename...Args>
inline void NLogErr(const std::string& func, const std::string& format, Args&&...args)
{
	printf("Error in function: %s ", func.c_str());
	printf(format.c_str(), std::forward<Args>(args)...);
	printf("\n");
}

inline void LogWar(std::string a_Text)
{
	printf("Warning: %s\n", a_Text.c_str());
}

inline void Log(const char* a_Text)
{
	printf("%s\n", a_Text);
}

inline std::string GetShaderLocation(Core::RenderDevice a_Device, std::string a_Path)
{
	std::string location;

	if(a_Device == Core::RenderDevice::OpenGL)
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