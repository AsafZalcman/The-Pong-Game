#include "RegularBall.h"
#include "Ball.h"
#include "Board.h"
#include "Tet.h"

void RegularBall::DoMiss(Ball& ball, Tettris& matrix, int boardSide, Board* board)
{
	goToMiddle(ball);
	handleMiss(ball, matrix, boardSide, board);
}

void RegularBall::DoCornerHit(Ball& ball, Tettris& , int, Board*) 
{	
	ball.changeYDirection(); 
	ball.changeXDirection();
}
void RegularBall::DoCenterHit(Ball& ball, Tettris& , int, Board* ) { ball.changeXDirection(); }
