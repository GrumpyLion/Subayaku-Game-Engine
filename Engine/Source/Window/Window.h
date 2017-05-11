#pragma once

#include "Interface\IWindow.h"
#include <Windows.h>

namespace Core
{
	class Window : public IWindow
	{
	private:
		HWND m_Handle{};
		HINSTANCE m_HInstance{};
		SEngineContext m_Context{};
		DWORD m_Style;
	public:
		~Window();

		bool Initialize(SEngineContext &a_EngineContext) override;
		bool Update() override;

		void Resize();

		static LRESULT CALLBACK WndProc(HWND a_hwnd, unsigned int a_Message, WPARAM a_wParam, LPARAM a_lParam);

		HWND GetHandle();
	};
}