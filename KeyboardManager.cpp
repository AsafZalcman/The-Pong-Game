#include <conio.h>
#include "KeyboardManager.h"

void KeyboardManager::registerKbListener(KeyboardEventListener* pKbListener, size_t len)
{
	const char* chars = pKbListener->getKbChars();  
	for (size_t i = 0; i < len; ++i) 
	{
		int index = getIndex(chars[i]);
		if (index != -1) 
		{
			kbListeners[index].push_back(pKbListener);
		}
	}
}

void KeyboardManager::handleKeyboard()
{
	for (int i = 0; i < 50; i++)
	{
		if (_kbhit())
		{
			char k = tolower(_getch());
			int index = getIndex(k);
			if (index != -1)
			{
				for (auto pKbListener : kbListeners[index])
				{
					pKbListener->handleKey(k);
				}
			}
		}
	}
}
