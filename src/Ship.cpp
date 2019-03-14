#include "Ship.h"

Ship::Ship(int row, int column, Direction dir, bool visibility, Color col)
{
	coordinates[0] = row;
	coordinates[1] = column;
	color = col;
	direction = dir;
	visible = visibility;
	next = NULL;
}

void Ship::setNext(Ship* n)
{
	next = n;
}

Direction Ship::getDirection()
{
	return direction;
}

Ship* Ship::getNext()
{
	return next;
}

Ship& Ship::operator++()
{
	Ship* current = this;
	while (current->getNext()) current = current->getNext();
	Ship* next = new Ship(current->getRow(), current->getColumn(), current->getDirection(), current->isVisible(), BROWN);

	switch (next->getDirection())
	{
	case UP:
		next->setRow(next->getRow() - 1);
		break;
	case DOWN:
		next->setRow(next->getRow() + 1);
		break;
	case RIGHT:
		next->setColumn(next->getColumn() + 1);
		break;
	case LEFT:
		next->setColumn(next->getColumn() - 1);
		break;
	}
	current->setNext(next);
	return *this;
}
