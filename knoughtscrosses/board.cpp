#include "board.h"
#include <iostream>



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
	legalMoves[place] = false; 
}

bool board::checkallwin(int place)
{
	bool key = false;
	
   //diag
	if (boardArr[2] == counter && boardArr[4] == counter && boardArr[6] == counter)
	{
		key = true; 
	}
	if (boardArr[0] == counter && boardArr[4] == counter && boardArr[8] == counter)
	{
		key = true;
	}
	//horizontol
	if (boardArr[0] == counter && boardArr[1] == counter && boardArr[2] == counter)
	{
		key = true;
	}
	if (boardArr[3] == counter && boardArr[4] == counter && boardArr[5] == counter)
	{
		key = true;
	}
	if (boardArr[6] == counter && boardArr[7] == counter && boardArr[8] == counter)
	{
		key = true;
	}
	

	//vertical
	if (boardArr[0] == counter && boardArr[3] == counter && boardArr[6] == counter)
	{
		key = true;
	}
	if (boardArr[1] == counter && boardArr[4] == counter && boardArr[7] == counter)
	{
		key = true;
	}
	if (boardArr[2] == counter && boardArr[5] == counter && boardArr[8] == counter)
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

bool board::legalMove(int place)
{

	return legalMoves[place];
}

void board::resetLegalMoves()
{
	for (int i = 0; i < 9; i++)
	{
		legalMoves[i] = true; 
	}
}

void board::refreshBoardArr()
{
	for (int i = 0; i < 9; i++)
	{
		boardArr[i] = 0; 
	}
}

bool board::checkDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (legalMoves[i] == true)
		{
			return false;
		}
	}
	return true;
}

int board::getCounter()
{
	return counter;
}

void board::startNewGame()
{
	resetLegalMoves();
	refreshBoardArr();
	counter = 1;
}
