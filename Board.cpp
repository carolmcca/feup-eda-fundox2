#include "iostream"
#include "Board.h"
#include "fundox.h"

using namespace std;

Board::Board(const int BOARD_SIZE) {
	this->size = BOARD_SIZE;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			this->board[i][j].first = ' ';
			this->board[i][j].second = nullptr;
		}
	}
}

//-------------------------------------------------------------

vector<vector<pair<char, Player*>>> Board::getBoard() const {
	return this->board;
}

//-------------------------------------------------------------

void Board::show() const {
	string letters = "ABCDEFGHIJKLM";
	cout << "\n    a b c d e f g h i j k l m" << endl;
	for (int i = 0; i < this->size; i++) {
		cout << " " << letters[i] << " " << bgGrey << " ";
		for (int j = 0; j < this->size; j++) {
			if (board[i][j].second != nullptr)
				cout << board[i][j].second->getColor();
			cout << board[i][j].first << " ";
		}
		cout << dfltColor << endl;
	}
}

//-------------------------------------------------------------

void Board::setEntry(int row, int col, const std::pair<char, Player*>& entry) {
	this->board[row][col] = entry;
}

//------------------------------------------------------------