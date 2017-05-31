#include "Input\Keyboard.h"
#include <memory>

namespace Core
{
	void Keyboard::Init()
	{	
		for (int i = 0; i < MAX_KEYS; i++)
			m_Keys[i] = false;

		for (int i = 0; i < MAX_KEYS; i++)
			m_PrevKeys[i] = false;
	}

	void Keyboard::Refresh()
	{
		memcpy(m_PrevKeys, m_Keys, sizeof(m_PrevKeys));
	}

	void Keyboard::Update()
	{
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_KeyDown[i] = !m_PrevKeys[i] && m_Keys[i];
		}
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

	bool Keyboard::IsKeyJustDown(int a_Key)
	{
		if (a_Key < 0 || a_Key >= MAX_KEYS)
			return false;

		return m_KeyDown[a_Key];
	}
}