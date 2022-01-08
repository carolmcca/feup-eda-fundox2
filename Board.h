#pragma once
#include "Player.h"

class Board {
public:
	Board(const int BOARD_SIZE);
	std::vector<std::vector<std::pair<char, Player*>>> getBoard() const;
	//void setBoardSize(int size);
	void setBoard(); //vetor de posições, 
	void show() const; //passar cor do player
private:
	std::vector<std::vector<std::pair<char, Player*>>> board; //?
	int boardSize;
};