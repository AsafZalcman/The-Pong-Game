#pragma once
#include "Bomb.h"
#include "Ball.h"
#include "Screen.h"
#include "Tet.h"

void Bomb::DoMiss(Ball& ball, Tettris & matrix, int boardSide, Board* board) 
{
	
	if (hitCenterDeadBoard(boardSide, matrix, ball))
	{
		if (!board->isLeftBoard())
		{
			matrix.handleFullColm(ball.getRightX() + 1 - board->MAX_RIGHT, board->getX());
			Board::lifeCounter(0, 1);
		}
		else
		{
			matrix.handleFullColm(ball.getLeftX() - 1 - Screen::MIN_X, board->getX());
			Board::lifeCounter(1, 0);
		}
		safeGraphic();
		board->moveBackFoward(-boardSide, 0, 1);
		ball.changeXDirection();
		goToMiddle(ball, ball.getxDirection());
		ball.changeToRegular();
		counter = 0;
	}
	else if (hitCornerDeadBoard(boardSide, matrix, ball))
	{
		if (!board->isLeftBoard())
		{
			matrix.handleFullColm(ball.getRightX() - board->MAX_RIGHT, board->getX());
			Board::lifeCounter(0, 1);
		}
		else
		{
			matrix.handleFullColm(ball.getLeftX() - Screen::MIN_X - 1, board->getX());
			Board::lifeCounter(1, 0);
		}
		safeGraphic();
		board->moveBackFoward(-boardSide, 0, 1);
		ball.changeXDirection();
		counter = 0;
		ball.changeToRegular();
		goToMiddle(ball, ball.getxDirection());
	}
	else if (hitScreenXEdge(ball))
	{
		
		if (!board->isLeftBoard())
		{
			matrix.handleFullColm(18, board->getX());
		}
		else
		{
			matrix.handleFullColm(0, board->getX());
		}
		if (board->getX() != 4 && board->getX() != 76) //Don't move the board back if it's on is start line.
		{
			board->moveBackFoward(-boardSide, 0, 1);
			(board->isLeftBoard() == true) ? Board::lifeCounter(1, 0) : Board::lifeCounter(0, 1);
		}
		else
		{
			setColor(COLOR::WHITE_TEXT);
			board->draw();
		}
		ball.changeXDirection();
		ball.changeToRegular();
		counter = 0;
		goToMiddle(ball, ball.getxDirection());
		safeGraphic();

	}
	else
		--counter;
}

void Bomb::DoCornerHit(Ball& ball, Tettris& matrix, int boardSide, Board* board)
{
	counter = 0;
	goToMiddle(ball);
	ball.changeToRegular();
	for (int i = 0; i < 3; ++i)
	{
		handleMiss(ball, matrix, boardSide, board);
	}
	bigMissGraphic();
}

void Bomb::DoCenterHit(Ball& ball, Tettris& matrix, int boardSide, Board* board)
{
	DoCornerHit(ball, matrix, boardSide, board);
}

void Bomb::count(Ball& ball)
{
	counter++;
	if (counter == 4)
	{
		ball.changeToRegular();
		counter = 0;
	}
}

void Bomb::safeGraphic()
{
	setColor(COLOR::PINK_FADE_BACKGROUND);
	gotoxy(35, 1);
	cout << "  NICE SAFE   !";
	Sleep(700);
	gotoxy(35, 1);
	setColor(COLOR::WHITE_TEXT);
	cout << "               ";
}

void Bomb::bigMissGraphic()
{
	setColor(COLOR::PINK_FADE_BACKGROUND);
	gotoxy(35, 1);
	cout << "   BIG MISS   !";
	Sleep(700);
	gotoxy(35, 1);
	setColor(COLOR::WHITE_TEXT);
	cout << "               ";
}