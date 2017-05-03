#pragma once

#include "Interface\IWindow.h"
#include <Windows.h>

namespace Core
{
	class CWindow : public IWindow
	{
	private:
		HWND m_Handle{};
		HINSTANCE m_HInstance{};
		SEngineContext m_Context{};

	public:
		~CWindow() override;

		bool Initialize(const SEngineContext &a_EngineContext) override;
		bool Update() override;
		bool Shutdown() override;

		void Resize();

		static LRESULT CALLBACK WndProc(HWND a_hwnd, unsigned int a_Message, WPARAM a_wParam, LPARAM a_lParam);

		HWND GetHandle();
	};
}