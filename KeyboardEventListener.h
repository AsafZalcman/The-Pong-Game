#pragma once

struct KeyboardEventListener 
{
	virtual void handleKey(char c) = 0;
	virtual  char* getKbChars() = 0 ;
public:
	virtual ~KeyboardEventListener() {}
};