#pragma once
#include "Functions.h"
#include "Enums.h"

//map is indexed by row-major

class Square
{
protected:
	int coordinates[2];
	Color color;
	string symbol;
	bool visible;

public:
	Square(int row = 0, int column = 0, Color col = WHITE, string ch = " ", bool visibility = true);

	void setRow(int row);
	void setColumn(int column);
	void setRowColumn(int row, int column);
	void setColor(Color col);
	void setCharacter(char ch);
	void setVisibility(bool vis);

	int getRow();
	int getColumn();
	Color getColor();
	string getCharacter();

	bool isVisible();
};
