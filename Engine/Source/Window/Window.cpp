#include "Window.h"
#include "Core\Engine.h"
#include "Input\InputManager.h"

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

		Core::Engine::StaticClass()->GetContext().xPos = (GetSystemMetrics(SM_CXSCREEN) - rect.right - rect.left) / 2;
		Core::Engine::StaticClass()->GetContext().yPos = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom - rect.top) / 2;

		if (a_EngineContext.IsFullScreen)
		{
			//We don't need borders if we're in fullscreen mode
			style = WS_POPUP;

			Core::Engine::StaticClass()->GetContext().xPos = 0;
			Core::Engine::StaticClass()->GetContext().yPos = 0;
			
			rect.left = 0;
			rect.top = 0;

			rect.right = GetSystemMetrics(SM_CXSCREEN);
			rect.bottom = GetSystemMetrics(SM_CYSCREEN);
		}

		m_Handle = CreateWindowEx(WS_EX_APPWINDOW,
			a_EngineContext.Title, a_EngineContext.Title, style,
			Core::Engine::StaticClass()->GetContext().xPos,
			Core::Engine::StaticClass()->GetContext().yPos,
			rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, m_HInstance, NULL);

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

		case WM_MOVE:
			Core::Engine::StaticClass()->GetContext().xPos = (int)(short)LOWORD(a_LParam);
			Core::Engine::StaticClass()->GetContext().yPos = (int)(short)HIWORD(a_LParam);
			break;

		case WM_KEYDOWN:
			Engine::StaticClass()->GetInputManager()->GetKeyboard()->KeyDown((int)a_WParam);
			break;

		case WM_KEYUP:
			Engine::StaticClass()->GetInputManager()->GetKeyboard()->KeyUp((int)a_WParam);
			break;

		case WM_RBUTTONUP:
			Engine::StaticClass()->GetInputManager()->GetMouse()->RightButton = false;
			break;

		case WM_RBUTTONDOWN:
			Engine::StaticClass()->GetInputManager()->GetMouse()->RightButton = true;
			break;

		case WM_LBUTTONUP:
			Engine::StaticClass()->GetInputManager()->GetMouse()->LeftButton = false;
			break;

		case WM_LBUTTONDOWN:
			Engine::StaticClass()->GetInputManager()->GetMouse()->LeftButton = true;
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