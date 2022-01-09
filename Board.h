#pragma once
#include "Player.h"

class Board {
private:
	std::vector<std::vector<std::pair<char, Player*>>> board; //?
	int size;
public:
	Board(const int BOARD_SIZE);
	std::vector<std::vector<std::pair<char, Player*>>> getBoard() const;
	//void setBoardSize(int size);
	void setEntry(int row, int col, const std::pair<char, Player*> &entry); //vetor de posições, 
	void show() const; //passar cor do player
};