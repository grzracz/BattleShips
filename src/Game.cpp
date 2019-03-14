#include "Game.h"

random_device rd;

Game::Game(string name)
{
	player_board = new Board(name, 10, 10);
	enemy_board = new Board("Computer", 10, 10);
	enemy_board->makeInvisible();
	message1 = "";
	message2 = "";
	message3 = "";
	message4 = "";
	message5 = "";
}

void Game::addComment(string com)
{
	message1 = message2;
	message2 = message3;
	message3 = message4;
	message4 = message5;
	message5 = com;
}

void Game::Show()
{
	system("cls");
	setConsoleColor();
	cout << endl << "  " << player_board->getName();
	for (int i = 0; i < (int)(30 - (player_board->getName().length())); ++i) cout << " ";
	setConsoleColor(WHITE);
	cout << "  ";
	setConsoleColor();
	cout << "      ";
	cout << enemy_board->getName() << endl;
	for (int i = 0; i < 32; ++i) cout << " ";
	setConsoleColor(WHITE);
	cout << "  ";
	setConsoleColor();
	cout << endl;
	for (int i = 0; i < 12; ++i)
	{
		cout << "  ";
		for (int j = 0; j < 12; ++j)
		{
			setConsoleColor(player_board->getSquare(i, j)->getColor());
			cout << " " << player_board->getSquare(i, j)->getCharacter();
		}
		setConsoleColor();
		cout << "      ";
		setConsoleColor(WHITE);
		cout << "  ";
		setConsoleColor();
		cout << "      ";
		for (int j = 0; j < 12; ++j)
		{
			Square* current = enemy_board->getSquare(i, j);
			if (current->isVisible())
			{
				setConsoleColor(current->getColor());
				cout << " ";
				cout << current->getCharacter();
			}
			else
			{
				setConsoleColor(DARK_BLUE);
				cout << "  ";
			}
		}
		setConsoleColor();
		cout << endl;
	}
	for (int i = 0; i < 32; ++i) cout << " ";
	setConsoleColor(WHITE);
	cout << "  ";
	setConsoleColor();
	cout << endl;
	for (int i = 0; i < 32; ++i) cout << " ";
	setConsoleColor(WHITE);
	cout << "  ";
	setConsoleColor();
	cout << endl;
	cout << "Captain's log:" << endl << endl;
	setConsoleColor(8);
	cout << "[5] " << message1 << endl;
	setConsoleColor(7);
	cout << "[4] " << message2 << endl;
	setConsoleColor(15);
	cout << "[3] " << message3 << endl;
	cout << "[2] " << message4 << endl;
	cout << "[1] " << message5 << endl;
	setConsoleColor();
}

int* Game::findPoint(Board* board, int* position, Direction direction)
{
	Square* temp;
	switch (direction)
	{
	case UP:
		while (true)
		{
			if (position[0] == 1) return NULL;
			position[0]--;
			temp = board->getSquare(position[0], position[1]);
			if ((temp->getColor() == LIGHT_BLUE))
			{
				return position;
			}
			else if (temp->getColor() == BLACK) return NULL;
		}
		break;
	case DOWN:
		while (true)
		{
			if (position[0] == 10) return NULL;
			position[0]++;
			temp = board->getSquare(position[0], position[1]);
			if ((temp->getColor() == LIGHT_BLUE))
			{
				return position;
			}
			else if (temp->getColor() == BLACK) return NULL;
		}
		break;
	case RIGHT:
		while (true)
		{
			if (position[1] == 10) return NULL;
			position[1]++;
			temp = board->getSquare(position[0], position[1]);
			if ((temp->getColor() == LIGHT_BLUE))
			{
				return position;
			}
			else if (temp->getColor() == BLACK) return NULL;
		}
		break;
	case LEFT:
		while (true)
		{
			if (position[1] == 1) return NULL;
			position[1]--;
			temp = board->getSquare(position[0], position[1]);
			if ((temp->getColor() == LIGHT_BLUE))
			{
				return position;
			}
			else if (temp->getColor() == BLACK) return NULL;
		}
		break;
	}
	return position;
}

int* Game::choosePoint(Board* board)
{
	int* position = new int[2]; //row, column
	position[0] = 5;
	position[1] = 5;
	while (board->getSquare(position[0], position[1])->getColor() != LIGHT_BLUE)
	{
		position[0] = rd() % 10 + 1;
		position[1] = rd() % 10 + 1;
	}

	Square* temp = board->getSquare(position[0], position[1]);
	Color temp_color = temp->getColor();
	bool temp_visibility = temp->isVisible();
	temp->setColor(RED);
	temp->setVisibility(true);
	Show();
	int* tmp_pos = NULL;
	while (true)
	{
		if (_kbhit())
		{
			switch (int(_getch()))
			{
			case 224:
				switch (int(_getch()))
				{
				case 72: //UP arrow
					tmp_pos = findPoint(board, position, UP);
					if (!tmp_pos) break;
					else position = tmp_pos;
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				case 80: //DOWN arrow
					tmp_pos = findPoint(board, position, DOWN);
					if (!tmp_pos) break;
					else position = tmp_pos;
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				case 77: //RIGHT arrow
					tmp_pos = findPoint(board, position, RIGHT);
					if (!tmp_pos) break;
					else position = tmp_pos;
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				case 75: //LEFT arrow
					tmp_pos = findPoint(board, position, LEFT);
					if (!tmp_pos) break;
					else position = tmp_pos;
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				}
				break;
			case 10:
			case 13:
				if (!(board->checkSquareForPoint(position[0], position[1]))) break;
				temp->setColor(temp_color);
				temp->setVisibility(temp_visibility);
				return position;
				break;
			}
			if (tmp_pos)
			{
				temp = board->getSquare(position[0], position[1]);
				temp->setColor(RED);
				temp->setVisibility(true);
				Show();
			}
		}
	}
}

bool Game::previewShip(Board* board, int* position, int length, Direction direction)
{
	Square* temp = board->getSquare(position[0], position[1]);
	switch (direction)
	{
	case UP:
		for (int i = 1; i < length; ++i)
		{
			if (!(board->checkSquareForShip(position[0] - i, position[1]))) return false;
		}
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0] - i, position[1])->setColor(BROWN);
		}
		Show();
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0] - i, position[1])->setColor(LIGHT_BLUE);
		}
		break;
	case DOWN:
		for (int i = 1; i < length; ++i)
		{
			if (!(board->checkSquareForShip(position[0] + i, position[1]))) return false;
		}
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0] + i, position[1])->setColor(BROWN);
		}
		Show();
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0] + i, position[1])->setColor(LIGHT_BLUE);
		}
		break;
	case RIGHT:
		for (int i = 1; i < length; ++i)
		{
			if (!(board->checkSquareForShip(position[0], position[1] + i))) return false;
		}
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0], position[1] + i)->setColor(BROWN);
		}
		Show();
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0], position[1] + i)->setColor(LIGHT_BLUE);
		}
		break;
	case LEFT:
		for (int i = 1; i < length; ++i)
		{
			if (!(board->checkSquareForShip(position[0], position[1] - i))) return false;
		}
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0], position[1] - i)->setColor(BROWN);
		}
		Show();
		for (int i = 0; i < length; ++i)
		{
			board->getSquare(position[0], position[1] - i)->setColor(LIGHT_BLUE);
		}
		break;
	}
	return true;
}

Ship* Game::createShip(Board* board, int length)
{
	int* point = choosePoint(board);
	Direction temp_direction = LEFT;
	bool preview = previewShip(board, point, length, temp_direction);
	if (!preview)
	{
		temp_direction = DOWN;
		preview = previewShip(board, point, length, temp_direction);
	}
	if (!preview)
	{
		temp_direction = RIGHT;
		preview = previewShip(board, point, length, temp_direction);
	}
	if (!preview)
	{
		temp_direction = UP;
		preview = previewShip(board, point, length, temp_direction);
	}
	if (!preview)
	{
		return NULL;
	}

	while (true)
	{
		if (_kbhit())
		{
			switch (int(_getch()))
			{
			case 224:
				switch (int(_getch()))
				{
				case 72: //UP arrow
					preview = previewShip(board, point, length, UP);
					if (preview) temp_direction = UP;
					break;
				case 80: //DOWN arrow
					preview = previewShip(board, point, length, DOWN);
					if (preview) temp_direction = DOWN;
					break;
				case 77: //RIGHT arrow
					preview = previewShip(board, point, length, RIGHT);
					if (preview) temp_direction = RIGHT;
					break;
				case 75: //LEFT arrow
					preview = previewShip(board, point, length, LEFT);
					if (preview) temp_direction = LEFT;
					break;
				}
				break;
			case 10:
			case 13:
				Ship* tmp_ship = new Ship(point[0], point[1], temp_direction);
				for (int i = 1; i < length; ++i) ++(*tmp_ship);
				return tmp_ship;
				break;
			}
		}
	}
}

void Game::buildFleet(Board* board)
{
	Fleet* temp_fleet = board->getFleet();
	for (int i = 0; i < temp_fleet->fourdeckers_amount; ++i)
	{
		Ship* temp = createShip(board, 4);
		while (!temp) temp = createShip(board, 4);
		temp_fleet->fourdeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->fourdeckers[i] = temp;
		Show();
	}
	for (int i = 0; i < temp_fleet->threedeckers_amount; ++i)
	{
		Ship* temp = createShip(board, 3);
		while (!temp) temp = createShip(board, 3);
		temp_fleet->threedeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->threedeckers[i] = temp;
		Show();
	}
	for (int i = 0; i < temp_fleet->twodeckers_amount; ++i)
	{
		Ship* temp = createShip(board, 2);
		while (!temp) temp = createShip(board, 2);
		temp_fleet->twodeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->twodeckers[i] = temp;
		Show();
	}
	for (int i = 0; i < temp_fleet->onedeckers_amount; ++i)
	{
		Ship* temp = createShip(board, 1);
		while (!temp) temp = createShip(board, 1);
		temp_fleet->onedeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->onedeckers[i] = temp;
		Show();
	}
}

Ship* Game::randomlyCreateShip(Board* board, int length)
{
	int* point = new int[2]; //row, column
	point[0] = rd() % 10 + 1;
	point[1] = rd() % 10 + 1;
	Direction temp_direction = Direction(rd() % 4);
	if (board->getSquare(point[0], point[1])->getColor() == BROWN) return NULL;
	bool preview = previewShip(board, point, length, temp_direction);
	for (int i = 0; i < 10; ++i)
	{
		if (!preview)
		{
			point[0] = rd() % 10 + 1;
			point[1] = rd() % 10 + 1;
			temp_direction = Direction(rd() % 4);
			preview = previewShip(board, point, length, temp_direction);
		}
	}
	if (!(board->checkSquareForPoint(point[0], point[1]))) return NULL;

	Ship* tmp_ship = new Ship(point[0], point[1], temp_direction, false);
	for (int i = 1; i < length; ++i) ++(*tmp_ship);
	return tmp_ship;
}

void Game::randomlyBuildFleet(Board* board)
{
	Fleet* temp_fleet = board->getFleet();
	for (int i = 0; i < temp_fleet->fourdeckers_amount; ++i)
	{
		Ship* temp = randomlyCreateShip(board, 4);
		while (!temp) temp = randomlyCreateShip(board, 4);
		temp_fleet->fourdeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->fourdeckers[i] = temp;
	}
	for (int i = 0; i < temp_fleet->threedeckers_amount; ++i)
	{
		Ship* temp = randomlyCreateShip(board, 3);
		while (!temp) temp = randomlyCreateShip(board, 3);
		temp_fleet->threedeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->threedeckers[i] = temp;
	}
	for (int i = 0; i < temp_fleet->twodeckers_amount; ++i)
	{
		Ship* temp = randomlyCreateShip(board, 2);
		while (!temp) temp = randomlyCreateShip(board, 2);
		temp_fleet->twodeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->twodeckers[i] = temp;
	}
	for (int i = 0; i < temp_fleet->onedeckers_amount; ++i)
	{
		Ship* temp = randomlyCreateShip(board, 1);
		while (!temp) temp = randomlyCreateShip(board, 1);
		temp_fleet->onedeckers[i] = temp;
		while (temp)
		{
			board->setSquare(temp->getRow(), temp->getColumn(), temp);
			temp = temp->getNext();
		}
		temp_fleet->onedeckers[i] = temp;
	}
}

int* Game::choosePointToShoot(Board* board)
{
	int* position = new int[2]; //row, column
	position[0] = 5;
	position[1] = 5;
	while (board->getSquare(position[0], position[1])->isVisible())
	{
		position[0] = rd() % 10 + 1;
		position[1] = rd() % 10 + 1;
	}

	Square* temp = board->getSquare(position[0], position[1]);
	Color temp_color = temp->getColor();
	bool temp_visibility = temp->isVisible();
	temp->setColor(RED);
	temp->setVisibility(true);
	Show();
	temp->setColor(temp_color);
	temp->setVisibility(temp_visibility);
	while (true)
	{
		if (_kbhit())
		{
			switch (int(_getch()))
			{
			case 224:
				switch (int(_getch()))
				{
				case 72: //UP arrow
					if (position[0] > 1) --position[0];
					else break;
					temp = board->getSquare(position[0], position[1]);
					temp_color = temp->getColor();
					temp_visibility = temp->isVisible();
					temp->setColor(RED);
					temp->setVisibility(true);
					Show();
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				case 80: //DOWN arrow
					if (position[0] < 10) ++position[0];
					else break;
					temp = board->getSquare(position[0], position[1]);
					temp_color = temp->getColor();
					temp_visibility = temp->isVisible();
					temp->setColor(RED);
					temp->setVisibility(true);
					Show();
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				case 77: //RIGHT arrow
					if (position[1] < 10) ++position[1];
					else break;
					temp = board->getSquare(position[0], position[1]);
					temp_color = temp->getColor();
					temp_visibility = temp->isVisible();
					temp->setColor(RED);
					temp->setVisibility(true);
					Show();
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				case 75: //LEFT arrow
					if (position[1] > 1) --position[1];
					else break;
					temp = board->getSquare(position[0], position[1]);
					temp_color = temp->getColor();
					temp_visibility = temp->isVisible();
					temp->setColor(RED);
					temp->setVisibility(true);
					Show();
					temp->setColor(temp_color);
					temp->setVisibility(temp_visibility);
					break;
				}
				break;
			case 10:
			case 13:
				return position;
				break;
			}

		}
	}
}

string Game::toCoordinates(int row, int column)
{
	string w = to_string(row - 1);
	char k = static_cast<char>('A' - 1 + column);
	return (k + w);
}

bool Game::hitSquare(Board* board, int* position)
{
	Square* temp = board->getSquare(position[0], position[1]);
	if (temp->isVisible()) return true;
	if (temp->getColor() == BROWN)
	{
		temp->setColor(GREY);
		temp->setVisibility(true);
		board->getSquare(position[0] - 1, position[1] - 1)->setVisibility(true);
		board->getSquare(position[0] - 1, position[1] + 1)->setVisibility(true);
		board->getSquare(position[0] + 1, position[1] - 1)->setVisibility(true);
		board->getSquare(position[0] + 1, position[1] + 1)->setVisibility(true);
		addComment(player_board->getName() + " is shooting at " + toCoordinates(position[0], position[1]) + "... HIT!");
		if (enemy_board->isFleetSunk())
		{
			addComment("");
			addComment("The winner is: " + player_board->getName() + ". Well done!");
			Show();
			cin.get();
			exit(0);
		}
		Show();
		return true;
	}
	else
	{
		temp->setVisibility(true);
		addComment(player_board->getName() + " is shooting at " + toCoordinates(position[0], position[1]) + "... MISS!");
		Show();
		return false;
	}
}

bool Game::computerHitSquare(Board* board)
{
	int row = rd() % 10 + 1;
	int column = rd() % 10 + 1;
	Square* temp = board->getSquare(row, column);
	if (temp->getColor() == LIGHT_BLUE)
	{
		temp->setColor(DARK_BLUE);
		addComment("The Computer is shooting at " + toCoordinates(row, column) + "... MISS!");
		Show();
		return false;
	}
	else if (temp->getColor() == DARK_BLUE) return true;
	else if (temp->getColor() == BROWN)
	{
		temp->setColor(GREY);
		if (board->getSquare(row - 1, column - 1)->getColor() != BLACK) board->getSquare(row - 1, column - 1)->setColor(DARK_BLUE);
		if (board->getSquare(row - 1, column + 1)->getColor() != BLACK) board->getSquare(row - 1, column + 1)->setColor(DARK_BLUE);
		if (board->getSquare(row + 1, column - 1)->getColor() != BLACK) board->getSquare(row + 1, column - 1)->setColor(DARK_BLUE);
		if (board->getSquare(row + 1, column + 1)->getColor() != BLACK) board->getSquare(row + 1, column + 1)->setColor(DARK_BLUE);
		addComment("The Computer is shooting at " + toCoordinates(row, column) + "... HIT!");
		if (player_board->isFleetSunk())
		{
			addComment("");
			addComment("The winner is: " + enemy_board->getName() + ". Well done!");
			Show();
			cin.get();
			exit(0);
		}
		Show();
		Sleep(1000);
		return true;
	}
	else return true;
}

Board* Game::getBoardAlly()
{
	return player_board;
}

Board* Game::getBoardEnemy()
{
	return enemy_board;
}

void Game::Play()
{
	Show();
	addComment("Welcome to Battleships!");
	addComment("Please deploy your fleet:");
	addComment("Move the cursor with arrow keys and choose a starting point by pressing Enter.");
	addComment("After choosing your starting point you can change the position of your ship");
	addComment("with arrow keys and confirm it by pressing Enter.");
	buildFleet(player_board);
	addComment("Your fleet has been deployed.");
	Show();
	randomlyBuildFleet(enemy_board);
	addComment("Enemy fleet had been deployed.");
	Show();
	int starting_player = rd() % 2;
	addComment(((starting_player == 1) ? player_board->getName() : enemy_board->getName()) + " begins. Good luck!");
	addComment(" ");
	Show();
	if (starting_player == 0) while (computerHitSquare(player_board));
	while (true)
	{
		while (hitSquare(enemy_board, choosePointToShoot(enemy_board)));
		while (computerHitSquare(player_board));
	}
}
