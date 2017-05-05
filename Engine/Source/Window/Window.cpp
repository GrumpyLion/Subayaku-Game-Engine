#include "Window.h"
#include "Core\Engine.h"
#include "Input\Keyboard.h"

namespace Core
{
	CWindow::~CWindow()
	{
		Shutdown();
	}

	bool CWindow::Initialize(const SEngineContext &a_EngineContext)
	{
		m_Context = a_EngineContext;

		WNDCLASSEX wc{};
		m_HInstance = GetModuleHandle(NULL);

		wc.lpfnWndProc = WndProc;
		wc.hInstance = m_HInstance;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = a_EngineContext.Title;
		wc.cbSize = sizeof(WNDCLASSEX);

		if (RegisterClassEx(&wc) == NULL)
		{
			MessageBox(NULL, L"RegisterClassEx failed", L"Error", MB_ICONERROR);
			return false;
		}

		DWORD style = WS_OVERLAPPEDWINDOW;

		//This is needed to resize the window. Without this the client size would't be correct
		RECT rect
		{
			0, 0, a_EngineContext.Width, a_EngineContext.Height
		};

		AdjustWindowRect(&rect, style, NULL);

		int xPos = (GetSystemMetrics(SM_CXSCREEN) - rect.right - rect.left) / 2;
		int yPos = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom - rect.top) / 2;

		if (a_EngineContext.IsFullScreen)
		{
			//We don't need borders if we're in fullscreen mode
			style = WS_POPUP;

			xPos = 0;
			yPos = 0;
			
			rect.left = 0;
			rect.top = 0;

			rect.right = GetSystemMetrics(SM_CXSCREEN);
			rect.bottom = GetSystemMetrics(SM_CYSCREEN);
		}

		m_Handle = CreateWindowEx(WS_EX_APPWINDOW,
			a_EngineContext.Title, a_EngineContext.Title, style,
			xPos, yPos, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, m_HInstance, NULL);

		//Window creation failed
		if (m_Handle == nullptr)
		{
			return false;
		}

		ShowWindow(m_Handle, SW_SHOW);
		SetForegroundWindow(m_Handle);
		SetFocus(m_Handle);
		
		return true;
	}
	
	bool CWindow::Update()
	{
		MSG msg{};

		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				return false;
		}
		return true;
	}

	void CWindow::Resize()
	{
		RECT rect;
		if (GetWindowRect(m_Handle, &rect))
		{
			Engine::StaticClass()->GetContext().Width = rect.right - rect.left;
			Engine::StaticClass()->GetContext().Height = rect.bottom - rect.top;
		}
	}

	LRESULT CWindow::WndProc(HWND a_HWND, unsigned int a_Message, WPARAM a_WParam, LPARAM a_LParam)
	{
		switch (a_Message)
		{
		case WM_SIZE:
		{
			static_cast<CWindow*>(Engine::StaticClass()->GetWindow())->Resize();
			break;
		}

		case WM_KEYDOWN:
			Engine::StaticClass()->GetKeyboard()->KeyDown((int)a_WParam);
			break;

		case WM_KEYUP:
			Engine::StaticClass()->GetKeyboard()->KeyUp((int)a_WParam);
			break;

		case WM_CLOSE:
			DestroyWindow(a_HWND);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(a_HWND, a_Message, a_WParam, a_LParam);
	}

	bool CWindow::Shutdown()
	{
		DestroyWindow(m_Handle);
		m_Handle = nullptr;

		UnregisterClass(m_Context.Title, m_HInstance);
		m_HInstance = nullptr;
		
		return true;
	}

	HWND CWindow::GetHandle()
	{	return m_Handle;	}
}