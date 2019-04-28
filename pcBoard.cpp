#include "pcBoard.h"

int pcBoard::getNextStep()
{
	static bool inRightPosition = true; //the board will hit the ball
	//calculate your dest only if needed
	if (Pball->getxDirection() == Ball::RIGHT && !isLeftBoard() && Pball->isInMiddle()
		|| Pball->getxDirection() == Ball::LEFT && isLeftBoard() && Pball->isInMiddle())
		inRightPosition=dest();

	// start taking steps to your dest

	if (nextSteps < 0)
	{
		nextSteps += 1;
		return 1;
	}

	else if (nextSteps > 0)
	{
		nextSteps -= 1;
		return -1;
	}
	else
	{
		//the board will hit the ball
		if (inRightPosition)
			avoidFromBomb();

		return 0;
	}
}

bool pcBoard::dest()
{
	int randAddition=getRandForLevel(), distLimit=Pball->getDistFromEdge(); // steps until screen edge
	int distBoard; // steps untill the ball hits the board
	int dir = Pball->getYDirection();
	int xBoard = getX();
	int yBall = Pball->getUpY();

	if (isLeftBoard()) 
	{
		distBoard = Pball->getLeftX() - 1 - xBoard; //making sure we always get center hit
	}
	else
	{
		distBoard = xBoard - 1 - Pball->getRightX();// making sure we always get center hit
	}

	while (distBoard > distLimit)//ball hits edge screen before hits the board
	{
		distBoard -= distLimit;
		yBall += distLimit*dir;//acording to the new location of the ball
		distLimit = 18; // distance between screen's bottom and top ( (-2) the ball "size")
		dir *= -1;
	}
	
	nextSteps = getUpY() - (distBoard*dir + yBall);

	if ( randAddition == 5) // 5 is a random number we chose to make sure the pcBoard is missing ever 10 or 40 turns
		                    // according to it's level 
	{
		if (isAdditionValid(5))
		nextSteps = getUpY() - (distBoard*dir + yBall) + randAddition;
		else
		{
			nextSteps = getUpY() - (distBoard*dir + yBall) - randAddition;
		}
		return false;//the board will miss the ball
	}
	return true;//the board will hit the ball
}
void pcBoard::avoidFromBomb()
{
	int distBoard = getX() - Pball->getRightX();
	int dir = 1;
	if (isLeftBoard())
	{
		dir = -1;
		distBoard = Pball->getLeftX() - getX();
	}

	//before distBoard == 13 the ball will get to the board as regular
	if (distBoard == 13 && Pball->isCurrentBallRegular() && Pball->getxDirection() == dir)
		changeBombComing(BombComing::RUN);

	//if the ball changed it's status
	if (!Pball->isCurrentBallRegular())
	{
		//this case - the board need to do a corner hit to save from the bomb and also save a regular miss
		if (getBombComing() == BombComing::RUN && distBoard == 12 && Pball->getxDirection() == dir)
		{
			int distLimit = Pball->getDistFromEdge();
			if (distLimit < 12 && isAdditionValid(nextSteps = 3 * Pball->getYDirection()))
				nextSteps = 3 * Pball->getYDirection();//make a corner hit

			else
				nextSteps = -3 * Pball->getYDirection();//make a corner hit

			changeBombComing(BombComing::CORNER);
		}

		//save from the bomb
		if (getBombComing() == BombComing::RUN &&  distBoard == 8 && Pball->getxDirection() == dir)
		{
			int randAddition = getRandForLevel();
			if (randAddition != 5)//save from bomb
			{
				if (isAdditionValid(6))//the board can go up 6 times
					nextSteps = 6;
				else
					nextSteps = -6;
			}

			changeBombComing(BombComing::STAY);
		}
	}

}
