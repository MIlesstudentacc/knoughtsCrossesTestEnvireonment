#pragma once
#include <vector>
class board
{
public: 
	int counter = 1; 
	int boardArr[9] = {0,0,0,0,0,0,0,0,0};
	
	bool legalMoves[9] = { true,true,true,true,true,true,true,true,true };
	
	int getBoardSize();

	bool checkWin(int place,int decreaser);

	void switchCounter();

	void setCounter(int place);

	bool checkallwin(int place); 


	void presentBoard();

	bool legalMove(int place); 
	
	void resetLegalMoves(); 

	void refreshBoardArr();

	bool checkDraw();

	int getCounter(); 

	void startNewGame(); 

	


};

