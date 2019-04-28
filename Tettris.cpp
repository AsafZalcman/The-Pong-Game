#include "Tet.h"

int Tettris::isColmFull() const // function returns -1 if non of the colms are full
{
	int colmfull = -1;
	for (int colm = 0; colm < Colms && (colmfull == -1); colm++)
	{
		colmfull = colm;
		for (int row = 0; row < Rows && (colmfull != -1); row++)
		{
			if (matrix[row][colm] == 0)
				colmfull = -1;
		}
	}
	return colmfull;
}

void Tettris::drowMatrix() const 
{
	setColor(COLOR::GRAY_TEXT);
	for (int i = 0; i < Rows; i++)
	{
		gotoxy(megicNumber, Screen::MIN_Y + i);
		for (int j = 0; j < Colms; j++)
			matrix[i][j] == 1 ? cout << "#" : cout << " ";
	}
}

void Tettris::fallBoard(Board copyBoard)
{
	int i = copyBoard.getX();
	//copyBoard.draw();

	while (i != Screen::BoardLimit::MAX_X && i != Screen::BoardLimit::MIN_X && isPlaceAvailable(i, copyBoard.getUpY()))
	{
		copyBoard.eraseBoard();
		copyBoard.moveBackFoward(dir, 0, 1);
		Sleep(100);
		setColor(COLOR::GRAY_TEXT);
		copyBoard.draw();
		i += dir;
	}
	// Update the Tetris board - adding the new dead board
	insertBoard(i, copyBoard.getUpY());
}

bool Tettris::isPlaceAvailable(int xTop, int yTop) const
{
	for (int row = yTop - Screen::MIN_Y, colm = xTop - megicNumber, i = 0; i < Board::Board_Size; i++) 
	{
		if (matrix[row + i][colm + dir] == 1)
			return false;
	}
	return true;
}

void Tettris::makeEmptyColm(int colm)
{
	for (int row = 0; row < Rows; row++)
		matrix[row][colm] = 0;
}

void Tettris::colorFullColm(int colm) const
{
	setColor(COLOR::GREEN_BACKGROUND);
	for (int i = 0; i < Rows; i++)
	{
		Sleep(15);
		gotoxy(colm + megicNumber, Screen::MIN_Y + i);
		cout << "#";
	}
	setColor(COLOR::PINK_TEXT);
	gotoxy(30, 1);
	cout << "YOU GAINED BACK 5 LINES!";
	Sleep(1300);
	gotoxy(30, 1);
	cout << "                        ";
}

//CheackDirection for right board: 1 
//                for lefr board: -1
//No reason to check colms after the board location
//So check every colm before the left (left-1, left-2....)
//So check every colm before the right (right+1, right+2....)
void Tettris::downAllBoards(int fullColm, int boardXposition) 
{
	int cheackDirection = dir*-1;
	int until = boardXposition - megicNumber;
	int j;

	for (j = fullColm; j + cheackDirection != until; j += cheackDirection)
	{
		for (int i = 0; i < Rows; i++)
		{
			matrix[i][j] = matrix[i][j + cheackDirection];
		}
	}
	makeEmptyColm(j);
}

void Tettris::insertBoard(int xTop, int yTop)
{
	for (int row = yTop - Screen::MIN_Y, colm = xTop - megicNumber, i = 0; i < Board::Board_Size; i++) //boardsize
	{
		matrix[row + i][colm] = 1;
	}
}

void Tettris::handleFullColm(int fullColmIndex, int boardX)
{
	downAllBoards(fullColmIndex, boardX);
	drowMatrix();
}
