#pragma once
#include "Ship.h"

class Fleet
{
	friend class Board;
	friend class Game;

protected:
	Ship** fourdeckers;
	Ship** threedeckers;
	Ship** twodeckers;
	Ship** onedeckers;
	int fourdeckers_amount, threedeckers_amount, twodeckers_amount, onedeckers_amount;

public:
	Fleet(int amount4 = 1, int amount3 = 2, int amount2 = 3, int amount1 = 4);
};
