#include "agent.h"
#include <ctime>

void agent::updateStateTree(int action)
{
	if (!lastState->checkTransitionExist(action))
	{
		State* newState = new State();
		newState->updateTransitions(action, newState);





	}







}

void agent::takeAction(bool maxOrMin)
{
	srand((unsigned)time(NULL));

	int random = rand() % 8;
	if (random > epsilon)
	{
		action = takeGreedy(maxOrMin); 
	}
	else
	{
		action = takeExplore(); 
	}

}

void agent::decayEpsilon()
{


}

int agent::takeGreedy(bool maxOrMin)
{
	int action;
	if (maxOrMin)
	{
		 action = maxGreed();
	}
	else
	{
		action = minGreed();
	}
	return action; 
	

	

}

int agent::takeExplore()
{


	srand((unsigned)time(NULL));

	int random = rand() % currentState->getLegalMoveSize();

	int move = currentState->getLegalMove(random);

	return move; 
}

int agent::minGreed()
{
	int* legalMoves = currentState->getLegalMoves();
	int min = legalMoves[0];
	for (int i = 1; i < currentState->getLegalMoveSize(); i++)
	{
		if (legalMoves[i] > min)
		{
			min = legalMoves[i];
		}
	}
	return min;
}
int agent::maxGreed() {
	int* legalMoves = currentState->getLegalMoves();
	int max = legalMoves[0];
	for (int i = 1; i < currentState->getLegalMoveSize(); i++)
	{
		if (legalMoves[i] > max)
		{
			max = legalMoves[i];
		}
	}
	return max;
}
