#pragma once
#include "board.h"
#include "agent.h"
class gameStarter
{

	board* myboard = new board();
public:
	void humanVsHuman();

	void AISelfPlay(agent* myAgent);

	void humanVSAi(agent* myAgent);

	void AIvsAI(agent* myAgent1, agent* myAgent2);
};

