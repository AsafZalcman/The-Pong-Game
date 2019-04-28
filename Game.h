#pragma once
#include "Tet.h"
#include "KeyBoardManager.h"
#include "Ball.h"

class Game: public KeyboardEventListener
{
	pcBoard pcLeft,pcRight;
	userBoard userLeft,userRight;
	Ball ball;
	Tettris tetMatrixL;
	Tettris tetMatrixR;
	KeyboardManager kbManager;
	KeyboardManager::SHOLD_I_STOP esc_flag;
	char kbchar[1];

public:
	enum class GameStatus{ OFF, ON };
	enum Players { UserVsUser = '1', UserVsPc = '2', PcVsPc = '3' };
	Game():
		userLeft ({ 4, 10, '#' },{ 4,12,'#' }, "qa"),
		userRight({ 76, 11, '#' }, { 76,13,'#' }, "pl"),
		ball ({ 39, 9, 'O' }, { 40, 11, 'O' }, "sk", 0),
		tetMatrixL({ 1,  -1 }),
		tetMatrixR({ 61, 1 }), 
		pcLeft({ 4, 10, '#' }, { 4,12,'#' }, &ball),
		pcRight({ 76, 11, '#' }, { 76,13,'#' }, &ball)
	{
		*kbchar = KeyboardManager::ESC;
		esc_flag = KeyboardManager::SHOLD_I_STOP::CONTINUE;
	}
	GameStatus run(bool firstGame,char chose, int levelL, int levelR);
	void startNewGame();
	void initPlayersInfo(Board*& pLeft, Board*& pRight, char chose, int levelL, int levelR);
	bool handleBallPosition(Board* board, Ball& ball, int boardSide, Tettris& matrix, Board::BallPosition state);
	bool isGameOver(int x) const 
	{
		return x > Board::MAX_LEFT && x < Board::MAX_RIGHT ;
	}
	void setPcLevels(int levelL, int levelR)
	{
		if (levelL != -1)
			pcLeft.pcBoard::setLevel(levelL);
		if (levelR != -1)
			pcRight.pcBoard::setLevel(levelR);
	}
	//KeyboardEventListener functions:
	virtual void handleKey(char c) { esc_flag = KeyboardManager::SHOLD_I_STOP::PAUSE; };
	virtual  char* getKbChars() { return kbchar; };

};
