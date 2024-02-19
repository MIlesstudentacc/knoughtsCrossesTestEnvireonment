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
	return legalMoveLength;
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
	int i = 0;
	std::vector<int> tempStorage;
	for (i = 0; i < 9; i++)
	{
		if (myboard->legalMove(i))
		{
			tempStorage.push_back(i);
		}
	}
	legalMoves = new int[i];
	for (int j = 0; j < tempStorage.size(); j++)
	{
		legalMoves[j] = tempStorage[j];
	}
	

	
	

}
