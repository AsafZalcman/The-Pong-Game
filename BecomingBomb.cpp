#pragma once
#include "BecomingBomb.h"
#include "Ball.h"
#include "Screen.h"
#include "Tet.h"

void BecomingBomb::DoMiss(Ball& ball, Tettris& matrix, int boardSide, Board* board )
{
	if (hitCenterDeadBoard(boardSide,matrix,ball) || 
		hitCornerDeadBoard(boardSide,matrix,ball) || 
		hitScreenXEdge(ball))
	{
		goToMiddle(ball);
		ball.changeToRegular();
		handleMiss(ball, matrix, boardSide, board);
		counter = 0;
	}
}

void BecomingBomb::DoCornerHit(Ball& ball, Tettris& matrix, int boardSide, Board* board)
{ 
	ball.changeToRegular();
	ball.changeYDirection();
	ball.changeXDirection();
	counter = 0;
}

void BecomingBomb::DoCenterHit(Ball& ball, Tettris& matrix, int boardSide, Board* board)
{ 
	ball.changeToRegular();
	ball.changeXDirection();
	counter = 0;
}

void BecomingBomb::count(Ball& ball)
{
	counter++;
	if (counter == 8)
	{
		ball.changeToBomb();
		counter = 0;
	}
}