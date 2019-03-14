#include "Board.h"

Board::Board(string name, int rows, int columns)
{
	player_name = name;
	row_amount = rows + 2;
	column_amount = columns + 2;
	board = new Square**[row_amount];
	for (int i = 0; i < row_amount; ++i) board[i] = new Square*[column_amount];
	for (int i = 0; i < row_amount; ++i)
	{
		for (int j = 0; j < column_amount; ++j)
		{
			board[i][j] = new Square(i, j, LIGHT_BLUE);
		}
	}
	for (int i = 0; i < row_amount; ++i)
	{
		board[i][0]->setColor(BLACK);
		board[i][column_amount - 1]->setColor(BLACK);
	}
	for (int i = 0; i < column_amount; ++i)
	{
		board[0][i]->setColor(BLACK);
		board[row_amount - 1][i]->setColor(BLACK);
	}
	for (int i = 1; i < row_amount - 1; ++i)
	{
		board[i][0]->setCharacter(i - 1 + '0');
		board[0][i]->setCharacter(i + 16 + '0');
	}

	fleet = new Fleet();
}

bool Board::isFleetSunk()
{
	for (int i = 1; i < row_amount - 1; ++i)
	{
		for (int j = 1; j < column_amount - 1; ++j)
		{
			if (board[i][j]->getColor() == BROWN) return false;
		}
	}
	return true;
};

void Board::addFleet()
{
	for (int i = 0; i < fleet->fourdeckers_amount; ++i)
	{
		Ship* temp = fleet->fourdeckers[i];
		if (temp)
		{
			while (temp)
			{
				board[temp->getRow()][temp->getColumn()] = temp;
				temp = temp->getNext();
			}
		}
	}

	for (int i = 0; i < fleet->threedeckers_amount; ++i)
	{
		Ship* temp = fleet->threedeckers[i];
		if (temp)
		{
			while (temp)
			{
				board[temp->getRow()][temp->getColumn()] = temp;
				temp = temp->getNext();
			}
		}
	}

	for (int i = 0; i < fleet->twodeckers_amount; ++i)
	{
		Ship* temp = fleet->twodeckers[i];
		if (temp)
		{
			while (temp)
			{
				board[temp->getRow()][temp->getColumn()] = temp;
				temp = temp->getNext();
			}
		}
	}

	for (int i = 0; i < fleet->onedeckers_amount; ++i)
	{
		Ship* temp = fleet->onedeckers[i];
		if (temp)
		{
			while (temp)
			{
				board[temp->getRow()][temp->getColumn()] = temp;
				temp = temp->getNext();
			}
		}
	}
}

void Board::makeInvisible()
{
	for (int i = 1; i < row_amount - 1; ++i)
	{
		for (int j = 1; j < column_amount - 1; ++j)
		{
			board[i][j]->setVisibility(false);
		}
	}
}

bool Board::checkSquareForPoint(int row, int column)
{
	if (!((board[row - 1][column - 1]->getColor() == LIGHT_BLUE) || (board[row - 1][column - 1]->getColor() == BLACK))) return false;
	else if (!((board[row - 1][column]->getColor() == LIGHT_BLUE) || (board[row - 1][column]->getColor() == BLACK))) return false;
	else if (!((board[row - 1][column + 1]->getColor() == LIGHT_BLUE) || (board[row - 1][column + 1]->getColor() == BLACK))) return false;
	else if (!((board[row][column - 1]->getColor() == LIGHT_BLUE) || (board[row][column - 1]->getColor() == BLACK))) return false;
	else if (!((board[row][column + 1]->getColor() == LIGHT_BLUE) || (board[row][column + 1]->getColor() == BLACK))) return false;
	else if (!((board[row + 1][column - 1]->getColor() == LIGHT_BLUE) || (board[row + 1][column - 1]->getColor() == BLACK))) return false;
	else if (!((board[row + 1][column]->getColor() == LIGHT_BLUE) || (board[row + 1][column]->getColor() == BLACK))) return false;
	else if (!((board[row + 1][column + 1]->getColor() == LIGHT_BLUE) || (board[row + 1][column + 1]->getColor() == BLACK))) return false;
	else return true;
}

bool Board::checkSquareForShip(int row, int column)
{
	if (board[row][column]->getColor() != LIGHT_BLUE) return false;
	else if (!((board[row - 1][column - 1]->getColor() == LIGHT_BLUE) || (board[row - 1][column - 1]->getColor() == BLACK))) return false;
	else if (!((board[row - 1][column]->getColor() == LIGHT_BLUE) || (board[row - 1][column]->getColor() == BLACK))) return false;
	else if (!((board[row - 1][column + 1]->getColor() == LIGHT_BLUE) || (board[row - 1][column + 1]->getColor() == BLACK))) return false;
	else if (!((board[row][column - 1]->getColor() == LIGHT_BLUE) || (board[row][column - 1]->getColor() == BLACK))) return false;
	else if (!((board[row][column + 1]->getColor() == LIGHT_BLUE) || (board[row][column + 1]->getColor() == BLACK))) return false;
	else if (!((board[row + 1][column - 1]->getColor() == LIGHT_BLUE) || (board[row + 1][column - 1]->getColor() == BLACK))) return false;
	else if (!((board[row + 1][column]->getColor() == LIGHT_BLUE) || (board[row + 1][column]->getColor() == BLACK))) return false;
	else if (!((board[row + 1][column + 1]->getColor() == LIGHT_BLUE) || (board[row + 1][column + 1]->getColor() == BLACK))) return false;
	else return true;
}

void Board::setSquare(int row, int column, Square* sq)
{
	board[row][column] = sq;
}

Square* Board::getSquare(int row, int column)
{
	return board[row][column];
}

string Board::getName()
{
	return player_name;
}

int Board::getRows()
{
	return row_amount;
}

int Board::getColumns()
{
	return column_amount;
}

Fleet* Board::getFleet()
{
	return fleet;
}
