#include "agent.h"
#include <ctime>
#include <iostream>
#include <bitset>

int agent::returntargetEpisodes()
{
	return target_Episodes;
}

void agent::updateStateTree(int action, State* newState)
{
	lastState->updateTransitions(action, newState);
}

void agent::takeAction(bool maxOrMin)
{
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
	if (episodes >= target_Episodes/10)//game tree complexity /10
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
	
	int legalMoveSize = currentState->getLegalMoveSize();
	int random = rand() % legalMoveSize;
	int move = currentState->getLegalMove(random);
	
	return move; 
}

int agent::minGreed()
{
	int i = 0;
	int* legalMoves = currentState->getLegalMoves();
	int minAction;
	if (!currentState->checkTransitionExist(legalMoves[i]))
	{
		minAction = legalMoves[i];
		return minAction;
	}
	double min = currentState->getTransition(legalMoves[i])->getValue();
	minAction = legalMoves[i];
	for (int j = i; j < currentState->getLegalMoveSize(); j++)
	{
		if (currentState->checkTransitionExist(legalMoves[j]))
		{
			double legalMoveValue = currentState->getTransition(legalMoves[j])->getValue();
			if (legalMoveValue < min)
			{
				min = legalMoveValue;
				minAction = legalMoves[j];
			}
		}
		else
		{
			minAction = legalMoves[j];
			return minAction;
		}
	}
	return minAction;
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
	int reward = 0; 
	int reward2 = 0;
	if (iterator % 2 == 1)
	{
		reward = -1;
		reward2 = 1;
	}
	else
	{
		reward = 1;
		reward2 = -1;
	}
	for (int i = 0; i < 2; i++)
	{
		while (iterator >= 0)
		{

			episode.at(iterator)->updateValue(reward, discount, learningRate, count);
			iterator = iterator - 2;
			count++;
		}
		reward = reward2;
		iterator = start - 1;
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
	refreshEpisode(); 
	lastState = nullptr;
	currentState = node; 

}


void agent::afterActionUpdates(long last_boardState, int action,int counter,board* myBoard)
{
	lastState = currentState;
	long new_boardState = calcNewBoardState(last_boardState, action,counter);
	State* toAdd = addToMap(new_boardState, myBoard);
	updateStateTree(action, toAdd);
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
	epsilon = -1; 
}

int agent::maxGreed() 
{
	int i = 0;
	int* legalMoves = currentState->getLegalMoves();
	/*std::cout << "ID" << std::endl;
	std::cout << currentState->id << std::endl;
	std::cout << "legal moves" << std::endl;
	for (int k = 0; k < currentState->getLegalMoveSize(); k++)
	{
		std::cout << legalMoves[k] << std::endl;
	}*/
	int maxAction;
	if (!currentState->checkTransitionExist(legalMoves[i]))
	{
		maxAction = legalMoves[i];
		return maxAction;
	}
	double max = currentState->getTransition(legalMoves[i])->getValue();
	maxAction = legalMoves[i];
	for (int j = i; j < currentState->getLegalMoveSize(); j++)
	{
		if (currentState->checkTransitionExist(legalMoves[j]))
		{
			double legalMoveValue = currentState->getTransition(legalMoves[j])->getValue();
			if (legalMoveValue > max)
			{
				max = legalMoveValue;
				maxAction = maxAction = legalMoves[j];
			}
		}
		else
		{
			maxAction = maxAction = legalMoves[j];
			return maxAction;
		}
	}
	return maxAction;
}

void agent::setToOriginState()
{
	currentState = node;
	lastState = nullptr; 

}

void agent::alwaysExplore()
{
	epsilon = 10;
}

int agent::gettotal_states()
{
	return latest_id;
}

State* agent::addToMap(long new_boardState,board* myBoard)
{
	State* Toadd = checkExist(new_boardState);
	if (Toadd == nullptr)
	{
		int size = stateSpace.size(); 
		Toadd = new State();
		Toadd->updateBoardState(new_boardState);//not running for anything other than node
		stateSpace[new_boardState] = Toadd;
		latest_id++;
		Toadd->updateLegalMoves(myBoard);
		//std::cout << "new state" + latest_id << std::endl;

	}
	else
	{
		latest_id = latest_id;
		
	}
	currentState = Toadd;
	return Toadd;

}

State* agent::checkExist(long new_boardState)
{
	if (stateSpace.find(new_boardState) != stateSpace.end())
	{
		State* foundState = stateSpace[new_boardState];
		return foundState;

	}
	else
	{
		return nullptr;
	}

}
long agent::calcNewBoardState(long old_boardState, int action,int counter)
{
	int actionAddOn = pow(3, action);
	actionAddOn = actionAddOn * counter; 
	return old_boardState + actionAddOn;
}


