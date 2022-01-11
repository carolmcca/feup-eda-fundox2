#pragma once
#include "utils.h"

class Board {
private:
	std::vector<std::vector<std::pair<char, int>>> board;
	int numRows;
	int numCols;
	std::string rowMarker;
	std::string colMarker;
public:
	Board();
	Board(const int BOARD_ROWS, const int BOARD_COLS);
	int getNumRows() const;
	int getNumCols() const;
	void setEntry(int row, int col, const std::pair<char, int> &entry);
	char getLetter(int row, int col) const;
	int getId(int row, int col) const;
	void show() const;
	int* getIdPointer(int row, int col);
};