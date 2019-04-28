#pragma once
#include "State.h"

class BecomingBomb : public State
{
	int counter;
public: 
	BecomingBomb(): State(COLOR::YELLOW_TEXT){ counter = 0; }
	virtual ~BecomingBomb() {};
	virtual void DoMiss(Ball& ball, Tettris& matrix, int boardSide, Board* board);
	virtual void DoCornerHit(Ball& ball, Tettris& matrix, int boardSide, Board* board);
	virtual void DoCenterHit(Ball& ball, Tettris& matrix, int boardSide, Board* board);
	virtual void count(Ball& ball);
};