// knoughtscrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "board.h"
#include <iostream>
#include "agent.h"
#include "gameStarter.h"
#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    std::vector<double> tdWinrates;
    std::vector<double> monteWinrates;
    srand((unsigned)time(NULL));
    agent* TdAgent; 
    agent* monteAgent; 
    gameStarter* myStarter = new gameStarter();
    gameStarter* myStarter2 = new gameStarter();
    //myStarter->AISelfPlay(TdAgent);
    //myStarter->humanVSAi(TdAgent);
    int tdWins = 0;
    int monteWins = 0;
    int totalWins = 0;
    for (int k = 0; k < 10; k++)
    {
   
     
        for (int j = 0; j < 10; j++)
        {
            TdAgent = new agent(true);
            monteAgent = new agent(false);
            for (int i = 0; i < 10; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                std::thread carloThread(&gameStarter::AISelfPlay, myStarter, std::ref(monteAgent));
                std::thread TDThread(&gameStarter::AISelfPlay, myStarter2, std::ref(TdAgent));
                carloThread.join();
                TDThread.join();
                myStarter->AIvsAI(TdAgent, monteAgent);

   


            }
            tdWins = tdWins + TdAgent->getWins();
            monteWins = monteWins + monteAgent->getWins();
            free(TdAgent);
            free(monteAgent);
         
        }
        totalWins = tdWins + monteWins;
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
        monteAgent->setNewEpisodes(total_Episode);
    }
        for (int i = 0; i < monteWinrates.size(); i++)
        {

            std::cout << monteWinrates[i] << std::endl;
            std::cout << tdWinrates[i] << std::endl;
        }

    

    
    



    


}

