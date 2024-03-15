#pragma once
#include "State.h"
#include <map>
class agent

{
private:

	bool TDOrCarlo;

	int gamesWon = 0;

	int episodes = 0; 

	std::vector<State*> episode; 


	bool maxOrMin = true; 

	double learningRate = 0.001;


	std::map<long, State*> stateSpace;


	State* node = new State();

	int epsilon = 9;

	State* lastState = nullptr;

	State* currentState = node; 

	int action = 0;

	float discount = 0.5;

	int total_episodes = 0;

	int latest_id = 1;



	int target_Episodes = 5;
public:

	agent(bool TDOrCarlo); 

	int returntargetEpisodes(); 

	void updateStateTree(int action, State* newState);

	void takeAction(bool maxOrMin);

	void decayEpsilon();

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

	void afterActionUpdates(long last_boardState, int action,int counter,board* myBoard);

	State* getCurrentState(); 

	int getEpisodeCount();

	void setAlwaysGreed();

	void setToOriginState(); 

	void alwaysExplore();

	int gettotal_states();


	State* addToMap(long new_boardState,board* myBoard);

	State* checkExist(long new_boardState);

	long calcNewBoardState(long old_boardState, int action,int counter);

	void TDCalc(double reward);

	bool getBackPropType();

	void increaseWins();

	int getWins();

	void setCurrentState(State* currentState);

	void setNewEpisodes(int newTargetEpisodes);
};

