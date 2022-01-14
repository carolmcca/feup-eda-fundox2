#include <iostream>
#include "Board.h"

using namespace std;

//------------------------------------------------------------

Board::Board() {
	this->board = {};
	this->numRows = 0;
	this->numCols = 0;
}

//------------------------------------------------------------

void Board::initBoard(const int BOARD_ROWS, const int BOARD_COLS) { //TODO: deixar assim?
	this->numRows = BOARD_ROWS;
	this->numCols = BOARD_COLS;
	this->board = vector<vector<pair<char, int>>>(this->numRows, vector<pair<char, int>>(this->numCols, pair<char, int> (' ', -1)));
	for (int i = 0; i < this->numRows; i++) {
		this->rowMarker.push_back('A' + i);
	}
	for (int i = 0; i < this->numCols; i++) {
		this->colMarker.push_back('a' + i);
		this->colMarker.push_back(' ');
	}
}

//------------------------------------------------------------

void Board::setEntry(int row, int col, const std::pair<char, int>& entry) { //TODO: por a fzr o par aqui dentro da função
	this->board[row][col] = entry;
}

//------------------------------------------------------------

int	Board::getNumRows() const {return this->numRows;}

int	Board::getNumCols() const {return this->numCols;}

char Board::getLetter(int row, int col) const {return this->board[row][col].first;}

int	Board::getId(int row, int col) const {return this->board[row][col].second;}

int* Board::getIdPointer(int row, int col) {return &(this->board[row][col].second);}

//------------------------------------------------------------

void Board::show() const {
	cout << endl << "    " << this->colMarker << endl;
	for (int i = 0; i < this->numRows; i++) {
		cout << " " << this->rowMarker[i] << " " << bgGrey << " ";
		for (int j = 0; j < this->numCols; j++) {
			if (this->board[i][j].second != -1)
				cout << colors[this->board[i][j].second];
			cout << this->board[i][j].first << " ";
		}
		cout << dfltColor << endl;
	}
}

//------------------------------------------------------------