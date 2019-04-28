#pragma once
#include "State.h"

class RegularBall : public State
{
public:
	RegularBall() :State(COLOR::GREEN_TEXT) {}
	virtual ~RegularBall() {};
	virtual void DoMiss(Ball& ball, Tettris & matrix, int boardSide, Board* board);
	virtual void DoCornerHit(Ball& ball, Tettris & matrix, int boardSide, Board* board);
	virtual void DoCenterHit(Ball& ball, Tettris & matrix, int boardSide, Board* board);
	virtual void count(Ball& ball) { return; } // No need to count nothing for regular ball
};