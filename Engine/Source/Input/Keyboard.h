#pragma once

const int MAX_KEYS = 256;

#define SUBA_KEY_SPACE              32
#define SUBA_KEY_0                  48
#define SUBA_KEY_1                  49
#define SUBA_KEY_2                  50
#define SUBA_KEY_3                  51
#define SUBA_KEY_4                  52
#define SUBA_KEY_5                  53
#define SUBA_KEY_6                  54
#define SUBA_KEY_7                  55
#define SUBA_KEY_8                  56
#define SUBA_KEY_9                  57
#define SUBA_KEY_A                  65
#define SUBA_KEY_B                  66
#define SUBA_KEY_C                  67
#define SUBA_KEY_D                  68
#define SUBA_KEY_E                  69
#define SUBA_KEY_F                  70
#define SUBA_KEY_G                  71
#define SUBA_KEY_H                  72
#define SUBA_KEY_I                  73
#define SUBA_KEY_J                  74
#define SUBA_KEY_K                  75
#define SUBA_KEY_L                  76
#define SUBA_KEY_M                  77
#define SUBA_KEY_N                  78
#define SUBA_KEY_O                  79
#define SUBA_KEY_P                  80
#define SUBA_KEY_Q                  81
#define SUBA_KEY_R                  82
#define SUBA_KEY_S                  83
#define SUBA_KEY_T                  84
#define SUBA_KEY_U                  85
#define SUBA_KEY_V                  86
#define SUBA_KEY_W                  87
#define SUBA_KEY_X                  88
#define SUBA_KEY_Y                  89
#define SUBA_KEY_Z                  90

#define SUBA_KEY_ESCAPE             27
#define SUBA_KEY_ENTER              13
#define SUBA_KEY_TAB                9
#define SUBA_KEY_BACKSPACE          8
#define SUBA_KEY_INSERT             45
#define SUBA_KEY_DELETE             46
#define SUBA_KEY_RIGHT              39
#define SUBA_KEY_LEFT               37
#define SUBA_KEY_DOWN               40
#define SUBA_KEY_UP                 38
#define SUBA_KEY_PAGE_UP            33
#define SUBA_KEY_PAGE_DOWN          34
#define SUBA_KEY_END                35
#define SUBA_KEY_CAPS_LOCK          20
#define SUBA_KEY_NUM_LOCK           144
#define SUBA_KEY_PAUSE              19
#define SUBA_KEY_F1                 112
#define SUBA_KEY_F2                 113
#define SUBA_KEY_F3                 114
#define SUBA_KEY_F4                 115
#define SUBA_KEY_F5                 116
#define SUBA_KEY_F6                 117
#define SUBA_KEY_F7                 118
#define SUBA_KEY_F8                 119
#define SUBA_KEY_F9                 120

namespace Core
{
	class Keyboard
	{
	private:
		bool m_Keys[MAX_KEYS];

	public:
		void Init();

		//Sets the indexed key down
		void KeyDown(int a_Key);
		void KeyUp(int a_Key);

		bool IsKeyDown(int a_Key);
	};
}