#pragma once

namespace Core
{
	class Mouse
	{
	private:
		int OldX = 0;
		int OldY = 0;

	public:

		int x = 0;
		int y = 0;

		int xD = 0;
		int yD = 0;

		bool LeftButton = false;
		bool RightButton = false;

		void Update();
		void SetMousePosition(int a_X, int a_Y);

	};
}