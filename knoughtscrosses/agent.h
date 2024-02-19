#pragma once
#include "State.h"
class agent

{
private:
	int episodes = 0; 

	std::vector<State*> episode; 


	bool maxOrMin = true; 

	float learningRate = 0.001;


	State* node = new State();

	int epsilon = 9;

	State* lastState;

	State* currentState = node; 

	int action = 0;

	float discount = 0.5;
public:
	void updateStateTree(int action);

	void takeAction(bool maxOrMin);

	void decayEpsilon();

	void backpropagate();

	int takeGreedy(bool maxOrMIn);

	int takeExplore(); 

	int maxGreed();

	int minGreed(); 

	void addToEpisode();

	void refreshEpisode(); 

	void increaseEpisodeCount();

	void monteCarlo(); 


	void setEpisodes(int episodes);

	int getAction(); 

	void agentCleanUp();

	void afterActionUpdates(); 

	tate* getCurrentState(); 
};

