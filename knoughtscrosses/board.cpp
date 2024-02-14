#include "board.h"

bool board::checkWin(int place,int decreaser)
{
	int lowestplace = place;
	int bound = decreaser * 2;

	while (lowestplace > bound)
	{
		lowestplace = lowestplace - decreaser;
	}
	for (int i = lowestplace; i < i + 6; i = i + decreaser)
	{
		if (boardArr[i] != counter)
		{
			return false;
		}
	}
	return true;

}

void board::switchCounter()
{
	if (counter == 1)
	{
		counter = 2;

	}
	else
	{
		counter = 1;
	}
}

void board::setCounter(int place)
{
	boardArr[place] = counter; 
}

bool board::checkallwin(int place)
{
	for (int i = 1; i < 5; i=i+2)
	{
		if (checkWin(place, i))
		{
			return true;
		}
	}


	
}
