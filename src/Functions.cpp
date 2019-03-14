#include "Functions.h"

void setConsoleColor(unsigned int color_number)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (color_number > 255) return;
	SetConsoleTextAttribute(console, color_number);
}
