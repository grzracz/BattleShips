#include "Square.h"

Square::Square(int row, int column, Color col, string ch, bool visibility)
{
	coordinates[0] = row;
	coordinates[1] = column;
	color = col;
	symbol = ch;
	visible = visibility;
}

void Square::setRow(int row)
{
	coordinates[0] = row;
}

void Square::setColumn(int column)
{
	coordinates[1] = column;
}

void Square::setRowColumn(int row, int column)
{
	setRow(row);
	setColumn(column);
}

void Square::setColor(Color col)
{
	color = col;
}

void Square::setCharacter(char ch)
{
	symbol = ch;
}

void Square::setVisibility(bool vis)
{
	visible = vis;
}

int Square::getRow()
{
	return coordinates[0];
}

int Square::getColumn()
{
	return coordinates[1];
}

Color Square::getColor()
{
	return color;
}

string Square::getCharacter()
{
	return symbol;
}

bool Square::isVisible()
{
	return visible;
}
