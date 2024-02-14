// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>

int main()
{
    bool win = false;
    while (!win)
    {
        int pos = 0;
        std::cout << "what position would you like to place your counter";
        std::cin >> pos;
        board* myboard = new board();
        myboard->setCounter(pos);

        win = myboard->checkallwin(pos);
        if (win)
        {
            std::cout << "noice";
        }
        myboard->switchCounter();
    }
 

    
        

}

