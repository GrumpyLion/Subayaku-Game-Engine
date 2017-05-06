#include "Mouse.h"
#include "Core\Engine.h"
#include "Input\InputManager.h"
#include <Windows.h>

namespace Core
{
	void Mouse::SetMousePosition(int a_X, int a_Y)
	{
		x = a_X;
		y = a_Y;
	}

	void Mouse::Update()
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		x = cursorPos.x - Core::Engine::StaticClass()->GetContext().xPos;
		y = cursorPos.y - Core::Engine::StaticClass()->GetContext().yPos;

		if (x < 0 || x > Core::Engine::StaticClass()->GetContext().Width ||
			y < 0 || y > Core::Engine::StaticClass()->GetContext().Height)
		{
			LeftButton = false;
			RightButton = false;
		}

		//Calculates the delta position
		xD = OldX - x;
		yD = OldY - y;

		OldX = x;
		OldY = y;
	}
}