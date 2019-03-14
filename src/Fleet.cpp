#include "Fleet.h"

Fleet::Fleet(int amount4, int amount3, int amount2, int amount1)
{
	fourdeckers_amount = amount4;
	threedeckers_amount = amount3;
	twodeckers_amount = amount2;
	onedeckers_amount = amount1;
	fourdeckers = new Ship*[fourdeckers_amount];
	threedeckers = new Ship*[threedeckers_amount];
	twodeckers = new Ship*[twodeckers_amount];
	onedeckers = new Ship*[onedeckers_amount];
}
