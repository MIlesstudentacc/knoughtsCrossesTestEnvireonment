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
    myAgent->getCurrentState()->updateLegalMoves(myboard);
    myAgent->getCurrentState()->id = 1;
    
   
   
    while (myAgent->getEpisodeCount() < myAgent->returntargetEpisodes())
    {

        //std::cout << "the current episodes" + myAgent->getEpisodeCount() << std::endl;
        State* current_state = myAgent->getCurrentState();
        int current_total = myAgent->gettotal_states();
        bool minOrMax = myboard->getCounter()%2;
    
        myAgent->takeAction(minOrMax);//if counter 2 false 
        int pos = myAgent->getAction();
        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);
            myAgent->afterActionUpdates(current_state->getBoardStateRepresentation(), pos,myboard->getCounter(),myboard);
            

            win = myboard->checkallwin(pos);
            if (win)
            {
                //std::cout << "noice";
                myboard->startNewGame();
                myAgent->monteCarlo();
                myAgent->agentCleanUp();
                
            }
            else if (myboard->checkDraw())
            {
                myboard->startNewGame();
                myAgent->agentCleanUp();
            }
            else
            {
                myboard->switchCounter();
            }
            //myboard->presentBoard();
        }
        else
        {
            myboard->presentBoard();
        }
    }
    std::cout << "finished" << std::endl;

}

void gameStarter::humanVSAi(agent* myAgent)
{
    myboard->startNewGame();
    myAgent->agentCleanUp();
    myAgent->setAlwaysGreed();
    //myAgent->alwaysExplore();
    bool win = false;
    myAgent->getCurrentState()->updateLegalMoves(myboard);
    myAgent->getCurrentState()->id = 1;
    
    int pos = 0;
    bool AIturn = true;
    for (int i = 0; i < 500; i++)
    {
        
      
        while (!win)
        {
            State* current_state = myAgent->getCurrentState();
            if (AIturn)
            {
                //std::cout << "the current episodes" + myAgent->getEpisodeCount() << std::endl;
            
                bool minOrMax = myboard->getCounter();
                myAgent->takeAction(minOrMax % 2);//if counter 2 false 
                pos = myAgent->getAction();
            }
            else
            {
               
                std::cout << "what position would you like to place your counter";
                std::cin >> pos;
            }

            if (myboard->legalMove(pos))
            {
                myboard->setCounter(pos);
                
                myAgent->afterActionUpdates(current_state->getBoardStateRepresentation(), pos, myboard->getCounter(),myboard);
                
                std::cout << "----------------------------------------" << std::endl;
                myboard->presentBoard();
                std::cout << "----------------------------------------" << std::endl;

                win = myboard->checkallwin(pos);
                if (win)
                {
                    if (AIturn == true)
                    {
                        std::cout << " AI wins";
                    }
                    else
                    {
                        std::cout << " Human wins";
                    }
                    win = false; 
                    myAgent->agentCleanUp();
                    myboard->startNewGame();
                    AIturn = false;

                }
                else if (myboard->checkDraw())
                {
                    std::cout << "draw";
                    myAgent->agentCleanUp();
                    myboard->startNewGame();
                    AIturn = false;

                }
                else
                {
                    myboard->switchCounter();
                }

                if (AIturn)
                {
                    AIturn = false;
                }
                else
                {
                    AIturn = true;
                }
            }
        }
    }

}
