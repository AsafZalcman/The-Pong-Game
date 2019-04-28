#pragma once

#include "Point.h"

using namespace std;

class Screen {
public:
	enum BoardLimit{ MIN_X = 1, MAX_X = 79, MIN_Y = 4, MAX_Y = 24 };
	static bool isOn_Y_Edge(const Point& p) 
	{
		return p.y == MIN_Y || p.y == MAX_Y;
	}

	static void printLines();
	
};