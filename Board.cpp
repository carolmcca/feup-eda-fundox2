#include <iostream>
#include "Board.h"
#include "utils.h"

using namespace std;

Board::Board() {

}

Board::Board(const int BOARD_SIZE) {
	this->size = BOARD_SIZE;
	for (int i = 0; i < this->size; i++) {
		this->board.push_back({});
		for (int j = 0; j < this->size; j++) {
			this->board[i].push_back(pair<char, int>(' ', -1));
		}
	}
}

//-------------------------------------------------------------

vector<vector<pair<char, int>>> Board::getBoard() const {
	return this->board;
}

//-------------------------------------------------------------

int Board::getSize() const {
	return this->size;
}
//-------------------------------------------------------------
void Board::show() const {
	string letters = "ABCDEFGHIJKLM";
	cout << "\n    a b c d e f g h i j k l m" << endl;
	for (int i = 0; i < this->size; i++) {
		cout << " " << letters[i] << " " << bgGrey << " ";
		for (int j = 0; j < this->size; j++) {
			if (board[i][j].second != -1)
				cout << colors[board[i][j].second];
			cout << board[i][j].first << " ";
		}
		cout << dfltColor << endl;
	}
}

//-------------------------------------------------------------

void Board::setEntry(int row, int col, const std::pair<char, int>& entry) { //TODO: por a fzr o par aqui dentro da função
	this->board[row][col] = entry;
}

//------------------------------------------------------------

pair<char, int> Board::getEntry(int row, int col) const{
	return this->board[row][col];
}

int* Board::getEntryPointer(int row, int col) {
	return &(this->board[row][col].second);
}