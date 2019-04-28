#include "State.h"
#include "Ball.h"
#include "Tet.h"

void State::goToMiddle(Ball & ball, int dirx)
{
	ball.eraseBall();//prevent erasing the board
	int randLocation = rand() % 13 + 5;
	ball.setLocation({ 39, randLocation, 'O' }, { 40, randLocation + 2, 'O' }, dirx);
}

bool State::hitCenterDeadBoard(int boardSide, Tettris& matrix, Ball& ball)
{
	if (boardSide == -1) //right
		return !matrix.isPlaceAvailable(ball.getRightX(), ball.getUpY());
	else
		return !matrix.isPlaceAvailable(ball.getLeftX(), ball.getUpY());
}

bool State::hitCornerDeadBoard(int boardSide, Tettris & matrix, Ball & ball)
{
	int i = ball.getUpY(), j = ball.getDownY();
	if (boardSide == -1) //right
		return (j != Screen::MAX_Y && i != Screen::MIN_Y && (!matrix.isPlaceAvailable(ball.getRightX(), i - 1) || 
			!matrix.isPlaceAvailable(ball.getRightX(), j - 1)));
	else
		return (j != Screen::MAX_Y && i != Screen::MIN_Y && (!matrix.isPlaceAvailable(ball.getLeftX(), i - 1) || 
			!matrix.isPlaceAvailable(ball.getLeftX(), j - 1)));
}

bool State::hitScreenXEdge(Ball & ball)
{
	return ball.getLeftX() == Screen::MIN_X || ball.getRightX() == Screen::MAX_X;
}

/* 
handleMiss taking care of:
[1] updating the matrix 
[2] making the board fall
[3] updating lifeCounter
 */
void State::handleMiss(Ball& ball, Tettris& matrix, int boardSide, Board* board)
{	
	int fullColmIndex;
	matrix.fallBoard(*board);
	fullColmIndex = matrix.isColmFull();

	if (fullColmIndex != -1) //Yay! we have a full colm!
	{
		matrix.colorFullColm(fullColmIndex);
		matrix.handleFullColm(fullColmIndex, board->getX());
		if (boardSide == -1) 
			Board::lifeCounter(0,5);
		else 
			Board::lifeCounter(5, 0);

		board->moveBackFoward(-boardSide, 0, 5);
	}
	else //non of the colms is full
	{
		board->moveBackFoward(boardSide, 0, 1);
		if (boardSide == -1) //right
			Board::lifeCounter(0, -1);
		else
			Board::lifeCounter(-1, 0);
	}
}

