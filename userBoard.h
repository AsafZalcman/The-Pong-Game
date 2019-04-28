#pragma once
#include "Screen.h"
#include "Board.h"
#include"KeyboardEventListener.h"

class userBoard :public Board,public KeyboardEventListener
{
	enum {kbTop, kbBottom};
	char kbChars[2];
	char currChar = 0;

public:
	userBoard(const Point& up1, const Point& bottom1, char* kbChars1) : Board (up1, bottom1)  
	{
		kbChars[kbTop] = kbChars1[kbTop];
		kbChars[kbBottom] = kbChars1[kbBottom];
	}
	virtual ~userBoard() {}
	virtual int userBoard::getNextStep();

	// KeyboardEventListener functions
	virtual char* getKbChars() { return kbChars; }
	virtual void handleKey(char c) { currChar = c;}
};