#pragma once
#include "Fleet.h"

class Board
{
protected:
	string player_name;
	int row_amount, column_amount;
	Square*** board;
	Fleet* fleet;
public:
	Board(string name, int rows, int columns);

	bool isFleetSunk();

	void addFleet();

	void makeInvisible();

	bool checkSquareForPoint(int row, int column);
	bool checkSquareForShip(int row, int column);

	void setSquare(int row, int column, Square* sq);

	Square* getSquare(int row, int column);
	string getName();
	int getRows();
	int getColumns();
	Fleet* getFleet();
};
