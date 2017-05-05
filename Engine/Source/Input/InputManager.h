#pragma once

#include "Keyboard.h"
#include "Mouse.h"

namespace Core
{
	class InputManager
	{
	private:
		Keyboard *m_Keyboard = nullptr;
		Mouse *m_Mouse = nullptr;

	public:
		~InputManager();

		void Initialize();

		void Update();

		Keyboard* GetKeyboard();
		Mouse* GetMouse();
	};
}