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
	if (episodes >= 195312)//game tree complexity /10
	{
		if (epsilon > 1)
		{
			epsilon = epsilon - 1;
			
		}
	}
	episodes = 0;
	

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
void agent::addToEpisode()
{
	episode.push_back(currentState);
}
void agent::refreshEpisode()
{
	episode.clear(); 
}
void agent::increaseEpisodeCount()
{
	episodes++;
}
void agent::monteCarlo()
{
	int start = episode.size();
	

	int iterator = start;

	int count = 0;
	
	while (iterator > 0)
	{
		count++;
		episode.at(iterator)->updateValue(1,discount,learningRate,count);
		iterator = iterator - 2;
			

			
	}
	iterator = start - 1;
	while (iterator > 0)
	{
		count++;
		episode.at(iterator)->updateValue(-1, discount, learningRate, count);
		iterator = iterator - 2;



	}

	
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
