#pragma once
#include "State.h"
class agent

{
	State* node = new State();

	int epsilon = 9;

	State* lastState;

	State* currentState = node; 

	int action = 0;

	void updateStateTree(int action);

	void takeAction();

	void decayEpsilon();

	void backpropagate();

	int takeGreedy();




	





};

