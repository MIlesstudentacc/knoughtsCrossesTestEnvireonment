#pragma once
#include "board.h"
#include "agent.h"
class gameStarter
{

	board* myboard = new board();
public:
	void humanVsHuman();

	void AISelfPlay(agent* myAgent);

};

