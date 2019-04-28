#pragma once
#include "userBoard.h"
#include "pcBoard.h"

using namespace std;
class Tettris 
{
	enum MatrixSize { Rows = 21, Colms = 19 };
	int matrix[Rows][Colms] = {0};
	const int megicNumber;
	const int dir; // -1 for left matrix, 1 for right matrix

	friend class Game;

public:
	Tettris(int mNumber, int d) : megicNumber(mNumber), dir(d) {};
	int isColmFull() const;
	void drowMatrix() const; 
	void fallBoard(Board cpBoard);
	void insertBoard(int xTop, int yTop);
	bool isPlaceAvailable(int xTop, int yTop) const;
	void makeEmptyColm(int colm);
	void Tettris::colorFullColm(int colm) const;
	void downAllBoards(int fullColm, int boardXposition);
	void handleFullColm(int fullColmIndex, int boardX); // Using down all board and drowMatrix
};
