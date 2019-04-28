#pragma once
#include "Point.h"
#include "RegularBall.h"
#include "BecomingBomb.h"
#include"KeyboardEventListener.h"
#include "Bomb.h"
#include "Screen.h"

class Ball : public KeyboardEventListener
{
	Point upLeft, downRight;
	int dir_x = (rand() % 2) * 2 - 1;
	int dir_y = (rand() % 2) * 2 - 1;
	char kbChars[2];
	int moveAt40Counter;
	int S_counter; // S_counter remembers: what was moveAt40Counter value last time the user presses S
	int K_counter; // same with k
	State* Current_Ball_State;
	Bomb bomb;
	BecomingBomb almost_bomb;
	RegularBall regular;

public:
	Ball(Point up1, Point down1, char* bombChars, int counter) :
		upLeft(up1), downRight(down1), Current_Ball_State(&regular), moveAt40Counter(counter)
	{
		kbChars[0] = bombChars[0];
		kbChars[1] = bombChars[1];
		K_counter = -4;
		S_counter = -4;
	} 
	virtual ~Ball() {}
	enum YDirection { Up = -1, Down = 1 };
	enum XDirection { LEFT = -1, RIGHT = 1 };
	void move();
	void drawBall() const;
	void eraseBall() const;

	virtual  char* getKbChars() { return kbChars; }
	virtual void handleKey(char c);
	bool isCurrentBallRegular() { return Current_Ball_State==&regular; }
	void changeToRegular() { Current_Ball_State = &regular; }
	void changeToBomb() { Current_Ball_State = &bomb; }

	void resetCounter() { moveAt40Counter = 0; }
	int getUpY() const
	{
		return upLeft.getY();
	}
	int getDownY() const
	{
		return downRight.getY();
	}

	//return the side "points" of the ball (which aren't save as data members)
	const int getRightX() const
	{
		return downRight.getX()+1;
	}

	int getLeftX() const
	{
		return upLeft.getX()-1;
	}

	void changeYDirection()
	{
		dir_y *= -1;
	}

	void changeXDirection()
	{
		dir_x *= -1;
	}

	YDirection getYDirection() const
	{
		return dir_y == -1 ? Up : Down;
	}

	XDirection getxDirection() const
	{
		return dir_x == -1 ? LEFT : RIGHT;
	}

	void miss(Board* pBoard, int boardSide, Tettris& mat)
	{
		Ball::Current_Ball_State->DoMiss(*this, mat, boardSide, pBoard);
	}

	void cornerHit(Board* pBoard, int boardSide, Tettris& mat)
	{
		Ball::Current_Ball_State->DoCornerHit(*this, mat, boardSide,pBoard);
	}

	void centerHit(Board* pBoard, int boardSide, Tettris& mat)
	{
		Ball::Current_Ball_State->DoCenterHit(*this, mat, boardSide, pBoard);
	}
	void move40count ()
	{
		if (isInMiddle())
			moveAt40Counter++;
	}
	
	void statesCounter(){ Current_Ball_State->count(*this); }
	COLOR getColor() const
	{
		return Current_Ball_State->getColor();
	}

	bool isInMiddle() const
	{
		return getLeftX() == 38;
	}

	void setLocation(const Point& upNewLocation, const Point& downNewLocation, int dir_x_set)
	{
		upLeft.setX(upNewLocation.getX());
		upLeft.setY(upNewLocation.getY());
		downRight.setX(downNewLocation.getX());
		downRight.setY(downNewLocation.getY());
		dir_x = dir_x_set;
		dir_y = (rand() % 2) * 2 - 1;
	}
	int getDistFromEdge()
	{
		if (getYDirection() == Ball::Up)
			return getUpY() - Screen::MIN_Y;
		else
			return Screen::MAX_Y - getDownY();
	}
};