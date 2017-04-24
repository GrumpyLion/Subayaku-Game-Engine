#pragma once

#define SAFE_DELETE(p) if(p != nullptr) {delete p; p = nullptr;}

#define SHUTDOWN_AND_DELETE(p) if(p!= nullptr) { p->Shutdown(); SAFE_DELETE(p); } 

#include <Windows.h>
#include <stdio.h>
#include <string>

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