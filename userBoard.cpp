#include "userBoard.h"
#include "Ball.h"

 int userBoard::getNextStep()
{
	// CurrChar is saving the char for the next step
	setColor(COLOR::WHITE_TEXT);

	if (currChar == kbChars[kbTop])
	{
		currChar = 0;
		return -1;
	}
	else if (currChar == kbChars[kbBottom])
	{
		currChar = 0;
		return 1;
	}
}
