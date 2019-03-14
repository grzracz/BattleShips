#pragma once
#include "Square.h"

class Ship : public Square
{
protected:
	Ship* next;
	Direction direction;

public:
	Ship(int row = 0, int column = 0, Direction dir = DOWN, bool visibility = true, Color col = BROWN);

	void setNext(Ship* n);

	Direction getDirection();
	Ship* getNext();

	Ship& operator++();
};
