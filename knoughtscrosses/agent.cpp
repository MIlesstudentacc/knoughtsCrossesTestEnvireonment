#include "agent.h"
#include <ctime>
#include <iostream>

void agent::updateStateTree(int action)
{
	lastState = currentState;
	if (!lastState->checkTransitionExist(action))
	{
		State* newState = new State();
		
		lastState->updateTransitions(action, newState);
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
	int legalMoveSize = currentState->getLegalMoveSize();
	int random = rand() % legalMoveSize;
	int move = currentState->getLegalMove(random);
	std::cout << random << std::endl;
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
	int iterator = start-1;
	int count = 0;
	
	while (iterator > 0)
	{
		
		episode.at(iterator)->updateValue(1,discount,learningRate,count);
		iterator = iterator - 2;
		count++;
	}
	iterator = start - 1;
	while (iterator > 0)
	{
		count++;
		episode.at(iterator)->updateValue(-1, discount, learningRate, count);
		iterator = iterator - 2;
	}

	
}
void agent::setEpisodes(int episodes)
{
	this->episodes = episodes;
}
int agent::getAction()
{
	return action;
}
void agent::agentCleanUp()
{
	increaseEpisodeCount();
	decayEpsilon(); 
	monteCarlo(); 
	refreshEpisode(); 
	currentState = node; 
}
void agent::afterActionUpdates()
{
	
	updateStateTree(action);
	addToEpisode(); 
}
State* agent::getCurrentState()
{
	return currentState;
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
