#pragma once
#include "State.h"

class Bomb: public State
{
	int counter;
public:
	Bomb() : State(COLOR::RED_TEXT)
	{
		counter = 0;
	}
	virtual ~Bomb() {};
	virtual void DoMiss(Ball& ball, Tettris & matrix, int boardSide, Board* board);
	virtual void DoCornerHit(Ball& ball, Tettris & matrix, int boardSide, Board* board);
	virtual void DoCenterHit(Ball& ball, Tettris & matrix, int boardSide, Board* board);
	void count(Ball& ball);
	void safeGraphic();
	void bigMissGraphic();
};
