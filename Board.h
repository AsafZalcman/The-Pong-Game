#pragma once
#include "Screen.h"

// forward declaration
class Ball;

class Board 
{
	Point top, bottom;

public:
	enum class BallPosition {MISSED, CENTER_HIT, CORNER_HIT, AWAY}; 
	enum { MAX_LEFT = 19, MAX_RIGHT = 61 };
	enum {Board_Size = 3};

	Board(const Point& up1, const Point& bottom1) : top(up1), bottom(bottom1) {}
	virtual ~Board() {}
	void draw() const;
	void move();
	void moveBackFoward(int dir_x, int dir_y, int times);
	void eraseBoard() const;
	BallPosition checkBallPosition(const Ball& ball) const;
	bool isLeftBoard() const { return getX() < 40; }
	virtual int getNextStep() { return 0; };
	int getX() const 
	{
		return top.getX();
	}
	int getUpY() const {
		return top.getY();
	}

	int getBottomY() const {
		return bottom.getY();
	}

	static void lifeCounter (int left, int right, bool reset = false)
	{
		static int left_life = 16;
		static int right_life = 16;
		if (reset)
		{
			right_life = 16;
			left_life = 16;
		}
		left_life += left;
		right_life += right;
		setColor(COLOR::TEAL_FADE_BACKGROUND);
		gotoxy(12, 1);
		cout << "  ";
		gotoxy(1, 1);
		cout << "Life left: " << left_life;
		gotoxy(77, 1);
		cout << "  ";
		gotoxy(65, 1);
		cout << "Life right: " << right_life;
	}
};
