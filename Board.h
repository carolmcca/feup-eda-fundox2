#pragma once
#include "Player.h"

class Board {
private:
	std::vector<std::vector<std::pair<char, int>>> board; //?
	int size;
public:
	Board();
	Board(const int BOARD_SIZE);
	std::vector<std::vector<std::pair<char, int>>> getBoard() const;
	int getSize() const;
	
	//void setBoardSize(int size);
	void setEntry(int row, int col, const std::pair<char, int> &entry); //vetor de posi��es, 
	std::pair<char, int> getEntry(int row, int col) const;
	void show() const; //passar cor do player
	int* getEntryPointer(int row, int col);
};