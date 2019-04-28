#include "Screen.h"

void Screen::printLines()
{
	{
		for (int i = 0; i <= Screen::MAX_X; i++)
		{
			gotoxy(i, 3);
			(i == 20 || i == 60) ? setColor(COLOR::RED_FADE_BACKGROUND) : setColor(COLOR::WHITE_FADE_BACKGROUND);
			cout << " ";
		}

		setColor(COLOR::RED_TEXT);
		gotoxy(15, 2);
		cout << "LEFT BORDER";
		gotoxy(55, 2);
		cout << "RIGHT BORDER";

		setColor(COLOR::PINK_FADE_TEXT);
		setColor(COLOR::WHITE_BACKGROUND);
	}
}
