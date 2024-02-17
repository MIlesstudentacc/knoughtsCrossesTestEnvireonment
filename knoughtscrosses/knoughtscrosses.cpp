// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>

int main()
{
    bool win = false;
    board* myboard = new board();
    while (!win)
    {
        int pos = 0;
        std::cout << "what position would you like to place your counter";
        std::cin >> pos;
        
        myboard->setCounter(pos);

        win = myboard->checkallwin(pos);
        if (win)
        {
            std::cout << "noice";
        }
        myboard->switchCounter();
        myboard->presentBoard();
    }
 

    
        

}

