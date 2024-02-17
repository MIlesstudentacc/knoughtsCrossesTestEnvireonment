#include "board.h"
#include <iostream>

bool board::checkWin(int place,int decreaser)
{
	int lowestplace = place;
	int bound = decreaser * 2;
	while (lowestplace - decreaser >= 0)
	{
		lowestplace = lowestplace - decreaser;
	}
	
	for (int i = lowestplace; i < (lowestplace+bound)+1; i = i + decreaser)
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
	bool key = false;
	
	if (checkWin(place, 1))
	{
		key=true;
	}
	if (checkWin(place, 3))
	{
		key = true;
	}

	if (checkWin(place, 4))
	{
		key = true;
	}
	if (key)
	{
		return true;
	}
	else
	{
		return false;
	}

	
}

void board::presentBoard()
{
	for (int i = 1; i < 10; i++)
	{
		if (i%3==0)
		{
			std::cout << boardArr[i-1] << std::endl;
		}
		else
		{
			std::cout << boardArr[i - 1];
		}
	
	}
}
