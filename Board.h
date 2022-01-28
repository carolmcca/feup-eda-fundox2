#pragma once
#include "utils.h"

class Board {
private:
	std::vector<std::vector<std::pair<char, int>>> board; /// game board: each entry is a pair <letter, corresponding player id>
	int numRows; /// number of rows of the board
	int numCols; /// number of columns of the board
	std::string rowMarker; /// string with the letters that represent each row (to be shown on the left of the board)
	std::string colMarker; /// string with the letters that represent each column (to be shown on top of the board)

public:
	Board();

	void initBoard(const int BOARD_ROWS, const int BOARD_COLS);
	void setEntry(int row, int col, const std::pair<char, int>& entry);

	int getNumRows() const;
	int getNumCols() const;
	char getLetter(int row, int col) const;
	int getId(int row, int col) const;
	int* getIdPointer(int row, int col);

	void show() const;
};