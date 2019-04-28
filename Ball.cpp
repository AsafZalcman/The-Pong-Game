#pragma once
#include "Ball.h"
#include "Screen.h"
#include "Tet.h"

void Ball::move()
{
	setColor(COLOR::YELLOW_TEXT);

	if (Screen::isOn_Y_Edge(upLeft) || Screen::isOn_Y_Edge(downRight))
	{
		dir_y *= -1;
	}

	upLeft.move(dir_x, dir_y);
	downRight.move(dir_x, dir_y);
}

void Ball::drawBall() const
{
	COLOR c = getColor();
	setColor(c);

	Point temp1 = upLeft, temp2 = downRight;
	temp1.draw();
	temp2.draw();

	for (int i = 0; i < 2; i++)
	{
		temp1.move(0, 1);
		temp1.draw();
		temp2.move(0, -1);
		temp2.draw();
	}
	temp1.move(-1, -1);
	temp1.draw();
	temp2.move(1, 1);
	temp2.draw();
}

void Ball::eraseBall() const
{
	setColor(COLOR::WHITE_TEXT);

	Point temp1 = upLeft, temp2 = downRight;
	temp1.erase();
	temp2.erase();

	for (int i = 0; i < 2; i++)
	{
		temp1.move(0, 1);
		temp1.erase();
		temp2.move(0, -1);
		temp2.erase();
	}
	temp1.move(-1, -1);
	temp1.erase();
	temp2.move(1, 1);
	temp2.erase();
}

void Ball::handleKey(char c)
{
	if (Current_Ball_State == &regular)
	{ 
		
		if (moveAt40Counter - S_counter >= 4 && (c == 's')) // moveAt40Counter counted 4 times
		{
			Current_Ball_State = &almost_bomb;
			S_counter = moveAt40Counter;
		}

		if (moveAt40Counter - K_counter >= 4 && (c == 'k'))
		{
			Current_Ball_State = &almost_bomb;
			K_counter = moveAt40Counter;
		}
	}
}