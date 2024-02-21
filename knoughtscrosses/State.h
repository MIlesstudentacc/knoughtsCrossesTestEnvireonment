#pragma once
#include <vector>
#include "board.h"
#include <iostream>
class State
{
private:
	State* transitions[9];

	int* legalMoves;

	int legalMoveLength;
	double value = 0;
	
public:
	int id = 0;
	
	double getValue();

	bool checkTransitionExist(int transition);

	void updateTransitions(int transition,State* newState);

	void updateLegalMoves(board* myboard);

	int getLegalMoveSize(); 

	int* getLegalMoves();
	
	int getLegalMove(int move);

	void updateValue(int reward,float discount,float learningRate,int episodePos);

	State* getTransition(int action);
	
};

