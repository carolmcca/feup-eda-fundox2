#include <iostream>
#include "Board.h"

using namespace std;

Board::Board() {
	this->board = {};
	this->size = 0;
}

Board::Board(const int BOARD_SIZE) {
	this->size = BOARD_SIZE;
	for (int i = 0; i < this->size; i++) {
		this->board.push_back({});
		this->rowMarker.push_back('A'+i);
		this->colMarker.push_back('a' + i);
		this->colMarker.push_back(' ');
		for (int j = 0; j < this->size; j++) {
			this->board[i].push_back(pair<char, int>(' ', -1));
		}
	}
}

//-------------------------------------------------------------

int Board::getSize() const {
	return this->size;
}
//-------------------------------------------------------------

void Board::show() const {
	cout << endl << "    " << this->colMarker << endl;
	for (int i = 0; i < this->size; i++) {
		cout << " " << this->rowMarker[i] << " " << bgGrey << " ";
		for (int j = 0; j < this->size; j++) {
			if (this->board[i][j].second != -1)
				cout << colors[this->board[i][j].second];
			cout << this->board[i][j].first << " ";
		}
		cout << dfltColor << endl;
	}
}

//-------------------------------------------------------------

void Board::setEntry(int row, int col, const std::pair<char, int>& entry) { //TODO: por a fzr o par aqui dentro da função
	this->board[row][col] = entry;
}

//------------------------------------------------------------

char Board::getLetter(int row, int col) const {
	return this->board[row][col].first;
}

//------------------------------------------------------------

int Board::getId(int row, int col) const{
	return this->board[row][col].second;
}

//------------------------------------------------------------

int* Board::getIdPointer(int row, int col) {
	return &(this->board[row][col].second);
}

//------------------------------------------------------------