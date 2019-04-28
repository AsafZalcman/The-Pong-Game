#include "Board.h"
#include "Ball.h"

void Board::draw () const
{
	Point temp = top;
	temp.draw();
	while (temp != bottom) 
	{
		temp.move(0, 1);
		temp.draw();
	} 
}

Board::BallPosition Board::checkBallPosition(const Ball& ball) const
{	
	// MISSED, CENTER_HIT, CORNER_HIT, AWAY
	int x_dist = getX() - ball.getRightX();

	if (top.getX() <= MAX_LEFT) // left board is playing
		x_dist = ball.getLeftX() - getX();
/*
	if (x_dist < 0)
	{
		return BallPosition::MISSED;
	}
	*/
	if (x_dist == 1 || x_dist == 0)
	{
		int board_upY = getUpY(), board_bottomY = getBottomY(), ball_downY = ball.getDownY(), ball_upY = ball.getUpY();
		Ball::YDirection ball_y_dir = ball.getYDirection();

		if (board_upY <= ball_upY + 1 && board_bottomY >= ball_downY - 1 && x_dist == 1 ||
			ball_upY == board_upY - 2 && ball_y_dir == Ball::Up && x_dist == 0 ||
			ball_upY == board_upY + 2 && ball_y_dir == Ball::Down && x_dist == 0)
		{
			return BallPosition::CENTER_HIT;
		}
		else
		{
			if (ball_upY == board_upY - 2 && ball_y_dir == Ball::Down
				|| ball_downY == board_bottomY + 2 && ball_y_dir == Ball::Up
				|| ball_downY == board_upY - 1 && x_dist == 0 && ball_y_dir == Ball::Down
				|| ball_upY == board_bottomY + 1 && x_dist == 0 && ball_y_dir == Ball::Up)
				return BallPosition::CORNER_HIT;
		}
	}
		if (x_dist <= 0)
		{
			return BallPosition::MISSED;
		}
		return BallPosition::AWAY;
	}


void Board::moveBackFoward(int dir_x, int dir_y, int times)
{
	for (int i = 0; i < times; i++)
	{
		setColor(COLOR::WHITE_TEXT);
		eraseBoard();
		bottom.move(dir_x, dir_y);
		top.move(dir_x, dir_y);
		draw();
		Sleep(30);
	}
}

void Board::eraseBoard() const
{
	Point temp = top;
	while (temp != bottom)
	{
		temp.erase();
		temp.move(0, 1);
	}
	temp.erase();
}

void Board::move()
{
	setColor(COLOR::WHITE_TEXT);

	int dir = getNextStep();
	if (dir == -1 && !Screen::isOn_Y_Edge(top)) //Up
	{
		bottom.erase();
		bottom.move(0, dir);
		top.move(0, dir);
		top.draw();
	}
	else if (dir == 1 && !Screen::isOn_Y_Edge(bottom))
	{
		top.erase();
		top.move(0, dir);
		bottom.move(0, dir);
		bottom.draw();
	}
}