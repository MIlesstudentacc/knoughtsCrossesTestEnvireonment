// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>
#include "agent.h"
#include "gameStarter.h"
int main()
{
    srand((unsigned)time(NULL));
    agent* thisAgent = new agent(true); 
    gameStarter* myStarter = new gameStarter(); 
    myStarter->AISelfPlay(thisAgent);
    myStarter->humanVSAi(thisAgent);

}

