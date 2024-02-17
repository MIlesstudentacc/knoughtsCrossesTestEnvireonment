#pragma once
#include <vector>
class board
{
public: 
	int counter = 1; 
	int boardArr[9] = {0,0,0,0,0,0,0,0,0};
	
	int getBoardSize();

	bool checkWin(int place,int decreaser);

	void switchCounter();

	void setCounter(int place);

	bool checkallwin(int place); 


	void presentBoard();
	

	





};

