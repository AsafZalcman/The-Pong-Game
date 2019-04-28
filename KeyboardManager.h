#pragma once
#include <list>
#include "userBoard.h"
#include"KeyboardEventListener.h"

class KeyboardManager 
{
	enum {NUM_CHARS = 27};
	// an array of 'char' => list of kbListener
	std::list<KeyboardEventListener*> kbListeners[NUM_CHARS];

	// helper method - get index in array per a given char
	int getIndex(char c)
	{
		if (c == ESC)
			return ESC - 1;

		if (c >= 'a' && c <= 'z')
			return c - 'a';
		if (c >= 'A' && c <= 'Z')
			return c - 'A';
		return -1;
	}
public:
	enum class SHOLD_I_STOP { PAUSE, CONTINUE };
	enum { ESC = 27 };
	void registerKbListener(KeyboardEventListener* pKbListener, size_t len);
	void handleKeyboard();
	void resetKbListener()
	{
		for (int i = 0;i<NUM_CHARS;i++)
		{
			kbListeners[i].clear();
		}
	}
};