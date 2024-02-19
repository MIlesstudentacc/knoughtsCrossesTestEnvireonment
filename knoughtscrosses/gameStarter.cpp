#include "gameStarter.h"
#include <iostream>

void gameStarter::humanVsHuman()
{
    bool win = false;

    while (!win)
    {
        int pos = 0;
        std::cout << "what position would you like to place your counter";
        std::cin >> pos;
        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);

            win = myboard->checkallwin(pos);
            if (win)
            {
                std::cout << "noice";
                myboard->startNewGame();
            }
            else if(myboard->checkDraw())
            {
                myboard->startNewGame();
            }
            myboard->switchCounter();
            myboard->presentBoard();
        }
    }
}

void gameStarter::AISelfPlay(agent* myAgent)
{
    bool win = false; 
    while (!win)
    {
        bool minOrMax = myboard->getCounter();
        myAgent->takeAction(minOrMax % 2);//if counter 2 false 
        int pos = myAgent->getAction();
        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);
            myAgent->afterActionUpdates();

            win = myboard->checkallwin(pos);
            if (win)
            {
                std::cout << "noice";
                myboard->startNewGame();
                myAgent->agentCleanUp();
            }
            else if (myboard->checkDraw())
            {
                myboard->startNewGame();
                myAgent->agentCleanUp();
            }
            myboard->switchCounter();
            myboard->presentBoard();
        }
    }

}
