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
    srand((unsigned)time(NULL));
    myAgent->getCurrentState()->updateLegalMoves(myboard);
    myAgent->getCurrentState()->id = 1;
    
    myAgent->alwaysExplore();
   
    while (myAgent->getEpisodeCount() < myAgent->returntargetEpisodes())
    {
        bool win = false;
        bool draw = false;
        while (!win && !draw)
        {
            //std::cout << "the current episodes" + myAgent->getEpisodeCount() << std::endl;
            State* current_state = myAgent->getCurrentState();
            int current_total = myAgent->gettotal_states();
            bool minOrMax = myboard->getCounter() % 2;

            myAgent->takeAction(minOrMax);//if counter 2 false 
            int pos = myAgent->getAction();
            if (myboard->legalMove(pos))
            {
                myboard->setCounter(pos);
                myAgent->afterActionUpdates(current_state->getBoardStateRepresentation(), pos, myboard->getCounter(), myboard);


                win = myboard->checkallwin(pos);
                if (win)
                {
                    //std::cout << "noice";
                    myboard->startNewGame();
                    if (myAgent->getBackPropType())
                    {
                        myAgent->monteCarlo();
                    }
                    else
                    {
                        if (minOrMax)
                        {
                            myAgent->TDCalc(-1);
                        }
                        else
                        {
                            myAgent->TDCalc(1);
                        }

                    }
                    myAgent->agentCleanUp();
                    win = true;

                }
                else if (myboard->checkDraw())
                {
                    myboard->startNewGame();
                    myAgent->agentCleanUp();
                    draw = true;
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
    }
   

}

void gameStarter::humanVSAi(agent* myAgent)
{
    myboard->startNewGame();
    myAgent->agentCleanUp();
    myAgent->setAlwaysGreed();
    //myAgent->alwaysExplore();

    myAgent->getCurrentState()->updateLegalMoves(myboard);
    myAgent->getCurrentState()->id = 1;
    
    int pos = 0;
    bool AIturn = true;
    for (int i = 0; i < 500; i++)
    {
        bool win = false;
        bool draw = false;
      
        while (!win && !draw)
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
                    win = true; 
                    myAgent->agentCleanUp();
                    myboard->startNewGame();
                    AIturn = false;

                }
                else if (myboard->checkDraw())
                {
                    draw = true;
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


void gameStarter::AIvsAI(agent* myAgent1,agent* myAgent2)
{
    agent* myAgentList[2] = { myAgent1,myAgent2 };
    myboard->startNewGame();
    agent* myAgent;
 
    bool win = false;
    bool draw = false;
    for (int i = 1; i >=0; i--)
    {
        myAgent = myAgentList[i];
        myAgent->agentCleanUp();
        myAgent->setAlwaysGreed();
        myAgent->getCurrentState()->updateLegalMoves(myboard);
        myAgent->getCurrentState()->id = 1;
    }


    while (!win && !draw)
    {
        State* current_state = myAgent->getCurrentState();
        int current_total = myAgent->gettotal_states();
        bool minOrMax = myboard->getCounter() % 2;

        myAgent->takeAction(minOrMax);//if counter 2 false 
        int pos = myAgent->getAction();
        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);
            myAgent->afterActionUpdates(current_state->getBoardStateRepresentation(), pos, myboard->getCounter(), myboard);
            current_state = myAgent->getCurrentState(); 
           

            win = myboard->checkallwin(pos);
            if (win)
            {
                //std::cout << "noice";
                win = true;
                myboard->startNewGame();
                myAgent->increaseWins();
                myAgent1->agentCleanUp();
                myAgent2->agentCleanUp();


            }
            else if (myboard->checkDraw())
            {
                draw = true;
                myboard->startNewGame();
                myAgent1->agentCleanUp();
                myAgent2->agentCleanUp();
            }
            else
            {
                myboard->switchCounter();
               


                myAgent = myAgentList[myboard->getCounter() - 1];
                myAgent->setCurrentState(current_state);
            }
            //myboard->presentBoard();
        }
        else
        {
            myboard->presentBoard();
        }
    }
    


}