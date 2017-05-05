#include "InputManager.h"

namespace Core
{
	void InputManager::Initialize()
	{
		m_Keyboard = new Keyboard();
		m_Keyboard->Init();

		m_Mouse = new Mouse();
	}

	InputManager::~InputManager()
	{
		delete m_Keyboard;
		delete m_Mouse;
	}

	void InputManager::Update()
	{
		m_Mouse->Update();
	}

	Keyboard* InputManager::GetKeyboard()
	{
		return m_Keyboard;
	}

	Mouse* InputManager::GetMouse()
	{
		return m_Mouse;
	}
}