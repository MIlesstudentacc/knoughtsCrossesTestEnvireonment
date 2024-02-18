#pragma once
#include <vector>
#include "board.h"
class State
{
public:
	State* transitions[9];

	int* legalMoves;

	
	int value = 0;

	void updateValue();

	int getValue();

	bool checkTransitionExist(int transition);

	void updateTransitions(int transition,State* newState);

	void updateLegalMoves(board* myboard);

	int getLegalMoveSize(); 

	int* getLegalMoves();
	

	
};

