// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>
#include "agent.h"
#include "gameStarter.h"
#include <thread>
int main()
{
    std::vector<double> monteWinrates;
    srand((unsigned)time(NULL));
    agent* TdAgent = new agent(true);
    agent* monteAgent = new agent(false);
    gameStarter* myStarter = new gameStarter();
    gameStarter* myStarter2 = new gameStarter();
    //myStarter->AISelfPlay(TdAgent);
    //myStarter->humanVSAi(TdAgent);
    int tdWins = 0;
    int monteWins = 0;
    int totalWins = 0;
    for (int k = 0; k < 10; k++)
    {
        agent* TdAgent = new agent(true);
        agent* monteAgent = new agent(false);
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 10; i++)
            {


                std::thread carloThread(&gameStarter::AISelfPlay, myStarter, std::ref(monteAgent));
                std::thread TDThread(&gameStarter::AISelfPlay, myStarter2, std::ref(TdAgent));
                carloThread.join();
                TDThread.join();
                myStarter->AIvsAI(TdAgent, monteAgent);

                tdWins = TdAgent->getWins();
                monteWins = monteAgent->getWins();





            }
            totalWins = totalWins + tdWins + monteWins;
            if (totalWins > 0)
            {

                double percentTd = (double)tdWins / totalWins;
                double percentMonte = (double)monteWins / totalWins;
                monteWinrates.push_back(percentMonte);
                tdWinrates.push_back(percentTd);
            }
            int total_Episode = TdAgent->returntargetEpisodes();
            total_Episode = total_Episode * 2;
            TdAgent->setNewEpisodes(total_Episode);
        }
        free(TdAgent);
        free(monteAgent);
    }
        for (int i = 0; i < monteWinrates.size(); i++)
        {

            std::cout << monteWinrates[i] << std::endl;
            std::cout << tdWinrates[i] << std::endl;
        }

    

    
    



    


}

