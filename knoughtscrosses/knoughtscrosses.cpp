// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>
#include "agent.h"
#include "gameStarter.h"
int main()
{
    agent* thisAgent = new agent(); 
    gameStarter* myStarter = new gameStarter(); 
    myStarter->AISelfPlay(thisAgent);

}

