#include "Game.h"

Game::GameStatus Game::run(bool firstGame ,char chose, int levelL, int levelR)
{
	Screen::printLines();
	esc_flag = KeyboardManager::SHOLD_I_STOP::CONTINUE; // will change when ESC is pressed

	kbManager.registerKbListener(this, 1); //registering ESC

	Board* BR[2]; 
	initPlayersInfo(BR[0], BR[1], chose, levelL, levelR);

	if (!firstGame)
	{
		tetMatrixL.drowMatrix();
		tetMatrixR.drowMatrix();
	}
	
	setColor(COLOR::WHITE_TEXT); 
	BR[0]->draw();
	BR[1]->draw();
	ball.drawBall();
	
	Board::lifeCounter(0, 0);

	bool endGame = false;
	// stae updates whenever ball's position is relavent to board's side
	// happens twice: (1) board's move (2) ball's move 
	Board::BallPosition state;
	while (!endGame)
	{
		ball.move40count();
		kbManager.handleKeyboard();
		ball.eraseBall();
		BR[1]->move();
		BR[0]->move();
		ball.move();
		ball.statesCounter();
		ball.drawBall();
		Sleep(30);
		
		if (esc_flag == KeyboardManager::SHOLD_I_STOP::PAUSE)
			return GameStatus::ON;
		if (ball.getxDirection() == Ball::RIGHT && BR[1]->getX() - ball.getRightX() <= 1) //the ball is "around" the right board
		{
			state = BR[1]->checkBallPosition(ball);
			endGame = handleBallPosition(BR[1], ball, -1, tetMatrixR, state);
		}
		else if (ball.getxDirection() == Ball::LEFT && ball.getLeftX() - BR[0]->getX() <= 1) //the ball is "around" the left board
		{
			state = BR[0]->checkBallPosition(ball);
			endGame = handleBallPosition(BR[0], ball, 1, tetMatrixL, state);
		}
		//ball.statesCounter();

	}
	return GameStatus::OFF; // LOSE
}

bool Game::handleBallPosition(Board* board, Ball& ball, int boardSide, Tettris& matrix, Board::BallPosition state)
{
	switch (state)
	{
	case Board::BallPosition::AWAY:
		break;
	case Board::BallPosition::MISSED:
	{
		ball.miss(board, boardSide, matrix);
		break;
	}
	case Board::BallPosition::CORNER_HIT:
	{
		ball.cornerHit(board, boardSide, matrix);
		break;
	}
	case Board::BallPosition::CENTER_HIT:
	{
		ball.centerHit(board, boardSide, matrix);
		break;
	}
	}
	return isGameOver(board->getX());
}

void Game::startNewGame()
{
	userLeft = { { 4, 10, '#' },{ 4,12,'#' }, "qa" };
	userRight = { { 76, 11, '#' },{ 76,13,'#' }, "pl" };
	ball = { { 39, 9, 'O' },{ 40, 11, 'O' }, "sk", 0 };
	pcLeft = { { 4, 10, '#' },{ 4,12,'#' }, &ball };
	pcRight = { { 76, 11, '#' },{ 76,13,'#' }, &ball };
	esc_flag = KeyboardManager::SHOLD_I_STOP::CONTINUE;
	ball.changeToRegular();
	Board::lifeCounter(0, 0, true);
	kbManager.resetKbListener();
	for (int i = 0; i < Tettris::Colms; i++)
	{
		tetMatrixL.makeEmptyColm(i);
		tetMatrixR.makeEmptyColm(i);
	}
}

//chose means: user's players choise from menu 
void Game::initPlayersInfo(Board*& pLeft, Board*& pRight, char chose, int levelL, int levelR)
{
	if (chose == Players::UserVsUser)
	{
		pLeft = &userLeft;
		pRight = &userRight;
		kbManager.registerKbListener(&userLeft, 2);
		kbManager.registerKbListener(&userRight, 2);
		kbManager.registerKbListener(&ball, 2);
	}
	else if (chose == Players::UserVsPc)
	{
		pLeft = &userLeft;
		kbManager.registerKbListener(&userLeft, 2);
		kbManager.registerKbListener(&ball, 1);
		pRight = &pcRight;			
		setPcLevels(levelL, levelR);
	}
	else  if (chose == Players::PcVsPc)
	{
		pLeft = &pcLeft;
		pRight = &pcRight;
		setPcLevels(levelL, levelR);
	}
}

