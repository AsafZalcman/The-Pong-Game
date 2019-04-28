#pragma once
#include "utils.h"
class Ball;
class Board;
class Tettris;

class State
{
	COLOR color;
	public:
	State(COLOR color) :color(color) {}
	virtual ~State() {};
	void State::goToMiddle(Ball & ball, int dirx = (rand() % 2) * 2 - 1); // defult random x direction
	bool hitCenterDeadBoard(int boardSide, Tettris& matrix, Ball& ball);
	bool hitCornerDeadBoard(int boardSide, Tettris& matrix, Ball& ball);
	bool hitScreenXEdge(Ball& ball);
	virtual void handleMiss(Ball& ball, Tettris& matrix, int boardSide, Board* board);
	virtual void DoMiss(Ball& ball,Tettris& matrix, int boardSide,Board* board) = 0;
	virtual void DoCornerHit(Ball& ball, Tettris& matrix, int boardSide, Board* board) =0;
	virtual void DoCenterHit(Ball& ball, Tettris& matrix, int boardSide, Board* board) =0;
	virtual void count(Ball& ball) = 0;
	COLOR getColor() { return color; }
};