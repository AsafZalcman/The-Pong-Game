#include "Menu.h"
#pragma once

void Menu::run() //program's menager
{
	printMenu();
	char choise; 
	char playersChoise = getChose(); 
	choise = playersChoise;
	int levelL = -1, levelR = -1;

	while (choise != EXIT)
	{
		system("cls");

		switch (choise)
		{
		case UserVsUser: {}
		case UserVsPc:{}
		case PcVsPc:
		{
			if (playersChoise == '2' || playersChoise == '3')
			{
				chosePcLevel(playersChoise, levelL, levelR);
			}

			if (!firstGame)
				pong.startNewGame();

			countDown();
			// In the first run of the program the values are initialized by the constructor. 
			// No double init is required
			setFirstGameOff();
		}
		case RESUME_GAME:
			setGameStatus(pong.run(firstGame,playersChoise, levelL, levelR)); //RUNNING THE GAME!
							        //return valuse: OFF (game over) ON (the user pressed ESC)
			break;
		case INSTRUCTIONS:
		{
			printInstructions();
			gotoxy(0, 0);
		}
			break;
		}
		system("cls");

		setColor(COLOR::WHITE_TEXT);
		gotoxy(0, 10);
		if (gameStatus == Game::GameStatus::OFF && choise != INSTRUCTIONS &&choise != RETURNFROMINST)
			printGameOver();
		else
			cout << "Enjoy your break, press (4) for continue" << endl;
		printMenu();
		choise = getChose();
		if (choise < '4' ) // game only intrest in players choise meaning: 1, 2, 3 
			playersChoise = choise;
	}
}

void Menu::printMenu() const
{
	setColor(COLOR::WHITE_TEXT);
	gotoxy(0, 11);
	cout << "(1) Start new game Humen vs Humen" << endl;
	cout << "(2) Start new game Humen vs Computer" << endl;
	cout << "(3) Start new game Computer vs Computer" << endl;

	if (gameStatus == Game::GameStatus::ON)
	{
		setColor(COLOR::WHITE_TEXT);
		cout << "(4) Resume game" << endl;
	}
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

	printPong();
	gotoxy(0, 18);
}

void Menu::chosePcLevel(char userChoise, int& levelL, int& levelR)
{
	char choiseR, choiseL;
	cout << "PLAYERS MENU" << endl;
	cout << "Chose right pc Level:" << endl;
	cout << "(1) BEST" << endl << "(2) GOOD" << endl << "(3) NOVICE" << endl;
	cin >> choiseR;
	while (choiseR != '1' && choiseR != '2' && choiseR != '3')
		cin >> choiseR;
	
	if (userChoise == '3')
	{
		cout << "Chose left pc Level:" << endl;
		cout << "(1) BEST" << endl << "(2) GOOD" << endl << "(3) NOVICE" << endl;
		cin >> choiseL;
		while (choiseL != '1' && choiseL != '2' && choiseL != '3')
			cin >> choiseL;

		if (choiseL == '1') 
			levelL = 0;
		else if (choiseL == '2') 
			levelL = 40;
			else levelL = 10;
	}

	if (choiseR == '1') levelR = 0;
	else if (choiseR == '2') levelR = 40;
	else levelR = 10;
}

char Menu::getChose() const //user's choise from menu
{
	char choise;
	cin >> choise;

	while ((choise != UserVsUser && choise != UserVsPc && choise != PcVsPc
		&& choise != INSTRUCTIONS  && choise != EXIT) 
		&& (gameStatus == Game::GameStatus::OFF || choise != RESUME_GAME))
	{
		cin >> choise;
	}
	return choise;
}

void Menu::printPong() const
{
	hideConsoleCursor();
	while (!_kbhit())
	{
		setColor((COLOR)(rand() % 15));
		gotoxy(20, 0); cout << " ______   _______   ____      __   ________               " << endl;
		gotoxy(20, 1); cout << "|  __  | |  ___  | |     \\   |  | |   _____|              " << endl;
		gotoxy(20, 2); cout << "| |__| | | |   | | |  |\\  \\  |  | |  | ____            " << endl;
		gotoxy(20, 3); cout << "|   ___| | |   | | |  | \\  \\ |  | |  ||__  \\           " << endl;
		gotoxy(20, 4); cout << "|  |     | |   | | |  |  \\  \\|  | |  |   | |          " << endl;
		gotoxy(20, 5); cout << "|  |     | |___| | |  |   \\     | |  |___| |          " << endl;
		gotoxy(20, 6); cout << "|__|     |_______| |__|    \\____| |________|              " << endl;
	}

	cout << endl << endl << endl;;
	setColor(COLOR::WHITE_TEXT);
}

void Menu::countDown() const
{
	setColor(COLOR::WHITE_TEXT);
	system("cls");
	setColor(COLOR::TEAL_TEXT);

	gotoxy(35, 7); cout << " _______  " << endl;
	gotoxy(35, 8); cout << "|____   | " << endl;
	gotoxy(35, 9); cout << " ____|  | " << endl;
	gotoxy(35, 10); cout <<"|____   | " << endl;
	gotoxy(35, 11); cout <<"     |  | "<< endl;
	gotoxy(35, 12); cout <<" ____|  | " << endl;
	gotoxy(35, 13); cout <<"|_______| " << endl;

	Sleep(700);
	system("cls");

	gotoxy(35, 7); cout << " _______  " << endl;
	gotoxy(35, 8); cout << "|____   | " << endl;
	gotoxy(35, 9); cout << " ____|  | " << endl;
	gotoxy(35, 10); cout << "|    ___| " << endl;
	gotoxy(35, 11); cout << "|   |     " << endl;
	gotoxy(35, 12); cout << "|   |___  " << endl;
	gotoxy(35, 13); cout << "|_______|  " << endl;

	Sleep(700);
	system("cls");
	 
	gotoxy(35, 7); cout << "   _____     " << endl;
	gotoxy(35, 8); cout << "  /     |  " << endl;
	gotoxy(35, 9); cout << " /  /|  |     " << endl;
	gotoxy(35, 10); cout<< "|__/ |  |       " << endl;
	gotoxy(35, 11); cout<< "     |  |   " << endl;
	gotoxy(35, 12); cout<< "  ___|  |__   " << endl;
	gotoxy(35, 13); cout<< " |_________|     " << endl;

	Sleep(700);
	system("cls");

}
void Menu::printGameOver() const
{ 
	system("cls");
	setColor(COLOR::WHITE_TEXT);
	gotoxy(18, 6);
	gotoxy(18, 7); cout << " ________    ________   __     __   ______     " << endl;
	gotoxy(18, 8); cout << "|   _____|  |   __   | |   \\  /  | |   ___|     " << endl;
	gotoxy(18, 9); cout << "|  | ____   |  |__|  | |    \\/   | |  |___     " << endl;
	gotoxy(18, 10); cout << "|  ||__  \\  |   __   | |  |\\_/|  | |   ___|    " << endl;
	gotoxy(18, 11); cout << "|  |   | |  |  |  |  | |  |   |  | |  |        " << endl;
	gotoxy(18, 12); cout << "|  |___| |  |  |  |  | |  |   |  | |  |___   " << endl;
	gotoxy(18, 13); cout << "|________|  |__|  |__| |__|   |__| |______|  " << endl;

	gotoxy(18, 14); cout << " _______   _        _   ______   _______        " << endl;
	gotoxy(18, 15); cout << "|  ___  | | |      | | |   ___| |   _   |                 " << endl;
	gotoxy(18, 16); cout << "| |   | | \\ \\      / / |  |___  |  |_|  |                  " << endl;
	gotoxy(18, 17); cout << "| |   | |  \\ \\    / /  |   ___| |  __  /                 " << endl;
	gotoxy(18, 18); cout << "| |   | |   \\ \\  / /   |  |     | |  \\ \\          " << endl;
	gotoxy(18, 19); cout << "| |___| |    \\ \\/ /    |  |___  | |   | |               " << endl;
	gotoxy(18, 20); cout << "|_______|     \\__/     |______| |_|   |_|              " << endl;

	cout << endl << endl;
	cout << "press 5 for menu";
	cout << endl;
	while (_getch() != '5');

	system("cls");
}

void Menu::printInstructions() const
{
	int choise;
	setColor(COLOR::WHITE_TEXT);
	cout << "Now that you are already champions in Pong-Tetris " << endl << 
		"it is time to move forward!" << endl << endl <<
		"So what's new?" << endl <<
		"Using the keys K and S (R\L) a bomb can be activated." << endl <<
		"just a monute...for 8 turns the ball will be in a position - almost a bomb." << endl <<
		"In this situation you are allowed to hit the ball." << endl <<
		"If you miss the ball - " << endl << 
		"as soon as the ball hits the dead board / screen's edge it is a miss." << endl <<
		"But be careful! After 8 steps almost a bomb will become a real bomb." << endl <<
		"If you hit the ball in a bomb mode? This is a BIG MISS! " << endl << 
		"Leading to a loss of 3 lives." << endl <<
		"If you are saved from the bomb? GREAT! You will gain one life back." << endl <<
		"Note - if you avoided the bomb and it also hits the board / screen's edge," << endl <<
		"it will delete the relevant line. Champion!" << endl <<
		"After a player has pressed a bomb" << endl << 
		"he will not be able to press again for 4 rounds" << endl << endl <<
		"(with a round defined as the ball's pass in the center of the field)." << endl <<
		"Last and Wonderful Upgrade -" << endl <<
		"You'll be able to play against the computer, " << endl <<
		"or let your computer play Vs computer and enjoy watching!" << endl <<
		"You can select computer levels (BEST, GOOD, NOVICE) " << endl << 
		"in a user friendly way in the main menu. " << endl << endl <<
		"ENJOY THE GAME!" << endl << endl;

	cout << "press (5) to go back to menu. bye!";

	cin >> choise;

	while (choise != 5)
		cin >> choise;

	system("cls");
}

