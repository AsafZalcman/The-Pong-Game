#pragma once
#include "Screen.h"
#include "Board.h"
#include "Ball.h"
class pcBoard :public Board
{
public:
	enum BombComing { STAY, RUN, CORNER };
private:
	Ball* Pball;
	int nextSteps; // pcboard knows it's next steps (num of steps)
	int level; // Levels: BEST = 1, GOOD = 40, NOVICE = 10 
	BombComing runFromBomb;
public:
	
	pcBoard(const Point& up1, const Point& bottom1, Ball* ball)
		: Board (up1, bottom1), Pball(ball), nextSteps(0),runFromBomb(STAY){}
	virtual ~pcBoard() {}
	virtual int getNextStep();
	bool dest();
	void avoidFromBomb();
	BombComing getBombComing() { return runFromBomb; }
	void changeBombComing(BombComing set) { runFromBomb = set; }
	void setLevel(int levelToSet) { level = levelToSet; }
	int getRandForLevel()
	{
		return level == 0 ? 0 : rand()%level;
	}

	bool isAdditionValid(int addition) 
	{ 
		if(addition>0)
		return getUpY() >= Screen::MIN_Y + addition; 
		
		else
			return getUpY()+2 <= Screen::MAX_Y + addition;
	}
};