#pragma once
#include "Game.h"
#include <conio.h>

using namespace std;
class Menu
{
	Game pong;
	bool firstGame = true;
	Game::GameStatus gameStatus = Game::GameStatus::OFF;
public:
	enum {UserVsUser = '1', UserVsPc = '2', PcVsPc = '3' ,RESUME_GAME = '4',RETURNFROMINST = '5', INSTRUCTIONS = '8', EXIT = '9' };
	void run();
	void setGameStatus(Game::GameStatus status) { gameStatus = status; }
	void setFirstGameOff() { firstGame = false; }
	char getChose() const;
	void printInstructions() const;
	void printPong() const;
	void printGameOver() const;
	void countDown() const;
	void chosePcLevel(char userChoise, int& levelL, int& levelR);
	void printMenu() const;
};