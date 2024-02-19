#pragma once
#include <vector>
#include "board.h"
class State
{
private:
	State* transitions[9];

	int* legalMoves;
public:
	
	int value = 0;

	

	int getValue();

	bool checkTransitionExist(int transition);

	void updateTransitions(int transition,State* newState);

	void updateLegalMoves(board* myboard);

	int getLegalMoveSize(); 

	int* getLegalMoves();
	
	int getLegalMove(int move);

	void updateValue(int reward,float discount,float learningRate,int episodePos);
	
};

