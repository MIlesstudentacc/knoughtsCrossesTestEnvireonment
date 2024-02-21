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
	currentState = lastState->getTransition(action);
}




void agent::takeAction(bool maxOrMin)
{
	srand((unsigned)time(NULL));

	int random = rand() % 10;

	
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
	if (episodes >= 1000000/10)//game tree complexity /10
	{
		if (epsilon > 1)
		{
			epsilon = epsilon - 1;
		
			episodes = 0;
			
		}
	}
	
	
	

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
	
	return move; 
}

int agent::minGreed()
{
	int i = 0;
	int* legalMoves = currentState->getLegalMoves();

	while (!currentState->checkTransitionExist(legalMoves[i]) && i < currentState->getLegalMoveSize() - 1)
	{
		i++;
	}
	if (i == currentState->getLegalMoveSize() - 1)
	{
		return takeExplore();
	}
	double min = currentState->getTransition(legalMoves[i])->getValue();
	for (int j = i; j < currentState->getLegalMoveSize(); j++)
	{
		if (currentState->checkTransitionExist(legalMoves[j]))
		{
			double legalMoveValue = currentState->getTransition(legalMoves[j])->getValue();
			if (legalMoveValue < min)
			{
				min = legalMoveValue;
			}
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
	this->episodes = episodes++;
	total_episodes = total_episodes++;
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
int agent::getEpisodeCount()
{
	return total_episodes;
}
void agent::setAlwaysGreed()
{
	int epsilon = 0; 
}
int agent::maxGreed() 
{
	int i = 0;
	int* legalMoves = currentState->getLegalMoves();

	while (!currentState->checkTransitionExist(legalMoves[i]) && i < currentState->getLegalMoveSize() - 1)
	{
		i++;
	}
	if (i == currentState->getLegalMoveSize() - 1)
	{
		return takeExplore();
	}
	double max = currentState->getTransition(legalMoves[i])->getValue();
	for (int j = i; j < currentState->getLegalMoveSize(); j++)
	{
		if (currentState->checkTransitionExist(legalMoves[j]))
		{
			double legalMoveValue = currentState->getTransition(legalMoves[j])->getValue();
			if (legalMoveValue > max)
			{
				max = legalMoveValue;
			}
		}
	}
	return max;
}
