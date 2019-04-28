#pragma once

#include <iostream>
#include "utils.h"

//Using the lecture's code
class Point 
{
	int x, y;
	char ch;
	void draw(char c) 
	{
		gotoxy(x, y);
		std::cout << c;
	}

	friend class Screen;

public:
	Point(int x1, int y1, char c): x(x1), y(y1), ch(c) {}
	void move(int dir_x, int dir_y) 
	{
		x += dir_x;
		y += dir_y;
	}
	void draw() 
	{
		draw(ch);
	}
	void erase() 
	{
		draw(' ');
	}
	int getX() const 
	{
		return x;
	}
	int getY() const 
	{
		return y;
	}
	void setY(int y1) 
	{
		y = y1;
	}
	void setX(int x1)
	{
		x = x1;
	}
	bool operator!=(const Point& other) const 
	{
		return x != other.x || y != other.y;
	}
};