#include "Keyboard.h"

namespace Core
{
	void Keyboard::Init()
	{	
		for (int i = 0; i < MAX_KEYS; i++)
			m_Keys[i] = false;
	}

	void Keyboard::KeyDown(int a_Index)
	{
		if (a_Index < 0 || a_Index >= MAX_KEYS)
			return;

		m_Keys[a_Index] = true;
	}

	void Keyboard::KeyUp(int a_Index)
	{
		if (a_Index < 0 || a_Index >= MAX_KEYS)
			return;

		m_Keys[a_Index] = false;
	}

	bool Keyboard::IsKeyDown(int a_Index)
	{
		if (a_Index < 0 || a_Index >= MAX_KEYS)
			return false;

		return m_Keys[a_Index];
	}
}