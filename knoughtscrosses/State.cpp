#include "State.h"

bool State::checkTransitionExist(int transition)
{
	if (transitions[transition] != nullptr)
	{
		return true;
	}
	else
	{
		return false; 
	}


	
}

void State::updateTransitions(int transition,State* newState)
{
	transitions[transition] = newState;
	
}


int State::getLegalMoveSize()
{
	return sizeof(legalMoves) / sizeof(int);
}

int* State::getLegalMoves()
{
	return legalMoves;
}

int State::getLegalMove(int move)
{
	return legalMoves[move];
}

void State::updateValue(int reward, float discount,float learningRate,int episodePos)
{
	value = learningRate * (reward * discount - value);

}

void State::updateLegalMoves(board* myboard)
{
	std::vector<int> tempStorage;
	for (int i = 0; i < 9; i++)
	{
		if (myboard->legalMove(i))
		{
			tempStorage.push_back(i);
		}
	}
	legalMoves = tempStorage.data();
	

}
