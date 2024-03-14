// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>
#include "agent.h"
#include "gameStarter.h"
#include <thread>
int main()
{
    std::vector<double> tdWinrates;
    srand((unsigned)time(NULL));
    agent* TdAgent = new agent(true); 
    agent* monteAgent = new agent(false);
    gameStarter* myStarter = new gameStarter(); 
    gameStarter* myStarter2 = new gameStarter(); 
    //myStarter->AISelfPlay(TdAgent);
    //myStarter->humanVSAi(TdAgent);
    int tdWins;
    int monteWins;
    for (int i = 0; i < 10; i++)
    {


        std::thread carloThread(&gameStarter::AISelfPlay, myStarter, std::ref(monteAgent));
        std::thread TDThread(&gameStarter::AISelfPlay, myStarter2, std::ref(TdAgent));
        carloThread.join();
        TDThread.join();
        myStarter->AIvsAI(TdAgent, monteAgent);

        tdWins = TdAgent->getWins();
        monteWins = monteAgent->getWins();

        int total_Wins = tdWins + monteWins;
        if (total_Wins > 0)
        {
            double percentTd = tdWins / total_Wins;

            tdWinrates.push_back(percentTd);
        }
    }
    std::cout << tdWins << std::endl;
    std::cout << monteWins << std::endl;
   
    
    
    



    


}

