#include "Window\Window.h"
#include "Core\Engine.h"
#include "Utilities\Utilities.h"
#include "Input\InputManager.h"

#include "Utilities\Event\SEventDesc.h"
#include "Utilities\Event\EventHandler.h"

namespace Core
{
	Window::~Window()
	{
		DestroyWindow(m_Handle);
		m_Handle = nullptr;

		UnregisterClass(m_Context.Title, m_HInstance);
		m_HInstance = nullptr;
	}

	bool Window::Initialize(SEngineContext &a_EngineContext)
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

		m_Style = WS_OVERLAPPEDWINDOW;

		//This is needed to resize the window. Without this the client size would't be correct
		RECT rect
		{
			0, 0, a_EngineContext.Width, a_EngineContext.Height
		};

		AdjustWindowRect(&rect, m_Style, NULL);

		Core::Engine::StaticClass()->GetContext().xPos = (GetSystemMetrics(SM_CXSCREEN) - rect.right - rect.left) / 2;
		Core::Engine::StaticClass()->GetContext().yPos = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom - rect.top) / 2;

		if (a_EngineContext.IsFullScreen)
		{
			//We don't need borders if we're in fullscreen mode
			m_Style = WS_POPUP;

			Core::Engine::StaticClass()->GetContext().xPos = 0;
			Core::Engine::StaticClass()->GetContext().yPos = 0;
			
			rect.left = 0;
			rect.top = 0;

			rect.right = GetSystemMetrics(SM_CXSCREEN);
			rect.bottom = GetSystemMetrics(SM_CYSCREEN);
		}

		Core::Engine::StaticClass()->GetContext().AdjustedWidth = rect.right - rect.left;
		Core::Engine::StaticClass()->GetContext().AdjustedHeight = rect.bottom - rect.top;

		m_Handle = CreateWindowEx(WS_EX_APPWINDOW,
			a_EngineContext.Title, a_EngineContext.Title, m_Style,
			Core::Engine::StaticClass()->GetContext().xPos,
			Core::Engine::StaticClass()->GetContext().yPos,
			rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, m_HInstance, NULL);

		//Window creation failed
		if (CheckIfPointerIsInvalid(m_Handle))
		{
			return false;
		}

		ShowWindow(m_Handle, SW_SHOW);
		SetForegroundWindow(m_Handle);
		SetFocus(m_Handle);
		
		return true;
	}
	
	bool Window::Update()
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

	void Window::Resize()
	{
		RECT rect;
		if (GetClientRect(m_Handle, &rect))
		{
			//AdjustWindowRect(&rect, m_Style, NULL);
			Engine::StaticClass()->GetContext().Width = rect.right - rect.left;
			Engine::StaticClass()->GetContext().Height = rect.bottom - rect.top;
		}
	}

	LRESULT Window::WndProc(HWND a_HWND, unsigned int a_Message, WPARAM a_WParam, LPARAM a_LParam)
	{
		switch (a_Message)
		{
		case WM_SIZE:
		{
			static_cast<Window*>(Engine::StaticClass()->GetWindow())->Resize();

			SEventDesc desc{};
			
			desc.Description = &Engine::StaticClass()->GetContext();
			desc.Event = EEvents::WINDOW_RESIZE;

			EventHandler::StaticClass()->ForceEvent(desc);
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

	HWND Window::GetHandle()
	{	return m_Handle;	}
}