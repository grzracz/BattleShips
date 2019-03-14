#pragma once
#include "Board.h"

class Game
{
protected:
	Board* player_board;
	Board* enemy_board;
	string message1, message2, message3, message4, message5;
public:

	Game(string name);

	string toCoordinates(int row, int column);
	void addComment(string com);
	void Show();

	int* findPoint(Board* board, int* position, Direction direction);
	int* choosePoint(Board* board);
	int* choosePointToShoot(Board* board);

	bool previewShip(Board* board, int* position, int length, Direction direction);
	Ship* createShip(Board* board, int length);
	void buildFleet(Board* board);
	Ship* randomlyCreateShip(Board* board, int length);
	void randomlyBuildFleet(Board* board);

	bool hitSquare(Board* board, int* position);
	bool computerHitSquare(Board* board);

	Board* getBoardAlly();
	Board* getBoardEnemy();

	void Play();
};
