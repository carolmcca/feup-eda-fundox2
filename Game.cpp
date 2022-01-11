#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Game.h"



using namespace std;

Game::Game(const Bag& bag, const Board& board, vector<Player>& players, int SCORE_MAX, const set<string>& dictionary) {
	this->bag = bag;
	this->board = board;
	this->SCORE_MAX = SCORE_MAX;
	this->INITIAL_NUM_PLAYERS = players.size();
	this->dictionary = dictionary;
	this->players = players;
	this->fillRack(true);
	this->numPlayers = this->INITIAL_NUM_PLAYERS;
}
//-------------------------------------------------------------

void Game::decreaseNumPlayers() {
	this->numPlayers--;
}

//-------------------------------------------------------------

//void Game::setBag(char letter = '0') {
//	if (letter == '0')
//		this->bag.removeLetter();
//	else
//		this->bag.addLetter(letter);
//}
//-------------------------------------------------------------

int Game::getINITIALNUMPLAYERS() const
{
	return INITIAL_NUM_PLAYERS;
}
//-------------------------------------------------------------

int Game::getNumPlayers() const
{
	return numPlayers;
}
//-------------------------------------------------------------
int Game::getSCOREMAX() const
{
	return SCORE_MAX;
}
//-------------------------------------------------------------

void Game::updateScores() {
	for (int i = 0; i < players.size(); i++)
		players[i].resetScore();

	for (int i = 0; i < board.getNumRows(); i++) {
		for (int j = 0; j < board.getNumCols(); j++) {
			if (board.getId(i, j) != -1)
				this->players[board.getId(i, j)].incScore(); //TODO: rever para tirar players do vetor
		}
	}
}

//-------------------------------------------------------------

void Game::showScores() const {
	cout << endl << setw(board.getNumCols() - 2) << " ";
	cout << "SCORE BOARD" << endl;

	int gaveUpSize = std::count_if(players.begin(), players.end(), [](const Player& p) { return p.getGaveUp(); });
	cout << setw(board.getNumCols() - players.size() + gaveUpSize + 1) << " ";
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].getGaveUp())
			cout << players[i].getColor() << setw(3) << players[i].getScore();
	}
	cout << dfltColor << endl;
}

//-------------------------------------------------------------

void Game::run() {
	bool isFirstWord = true;
	int current = this->numPlayers - 1;
	int passTurns = 0;
	int passRounds = 0;

	while (this->players[current].getScore() < this->SCORE_MAX && passRounds < 3 && this->numPlayers > 1) {
		current = (current + 1) % this->INITIAL_NUM_PLAYERS;
		if (this->players[current].getGaveUp())
			continue;
		
		bool restoreRack = (passRounds > 0 && passTurns == 0); //TODO: está a mudar rack quando P P P P G (4 jog)
		this->fillRack(restoreRack);
		this->showScores();
		this->board.show();
		this->rack.show(this->board.getNumCols());
		Turn turn;
		
		string message = players[current].getColor()+players[current].getName()+"'s turn"+dfltColor;
		TurnPlay input = turn.readWord(message, this->dictionary);
		switch (input) {
		case PASS:
			passRounds += (passTurns + 1) / numPlayers;
			passTurns = (passTurns + 1) % numPlayers;
			continue;
		case GIVEUP:
			decreaseNumPlayers();
			passRounds += passTurns / numPlayers;
			players[current].setGaveUp(true);
			continue;
		case PLAY:
			passTurns = 0;
			passRounds = 0;
		}
		
		turn.readPosition();
		turn.readDirection();

		bool validPosition = true;
		bool isConnected = isFirstWord;
		vector<char> possibleRack = checkExistingLetters(turn, validPosition, isConnected);
		if (validPosition && checkWordPlacement(turn, players[current], changePlayer, isConnected) && isConnected) {
			isFirstWord = false;
			this->rack.setRack(possibleRack);
			for (int i = 0; i < turn.getWord().length(); i++) {
				pair<char, int> entry = pair<char, int>(turn.getWordLetter(i), current);
				if (turn.getIsVertical())
						board.setEntry(turn.getRow() + i, turn.getCol(), entry);
				else
						board.setEntry(turn.getRow(), turn.getCol() + i, entry);
			}
			for (int i = 0; i < changePlayer.size(); i++)
				*changePlayer[i] = current;

			updateScores();
		}
		else {
			passTurns++;
		}
	}
	showScores();
	this->board.show();
}
//-------------------------------------------------------------
void Game::setWinnerPlayers()
{
	int numWinners = 0;
	int maxScore = -1;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].getGaveUp()) {
			if (players[i].getScore() > maxScore) {
				winnerPlayers.clear();
				winnerPlayers.push_back(&players[i]);
				maxScore = players[i].getScore();
			}
			else if (players[i].getScore() == maxScore) {
				winnerPlayers.push_back(&players[i]);
			}
		}
	}
}

//-------------------------------------------------------------


void Game::fillRack(bool restoreRack) {
	if (restoreRack) {  //quando queremos mandar a rack de volta para a bag e fazer uma nova?
		while (this->rack.getSize()>0) {
			char letter = this->rack.getLastLetter();
			// insert the letter extracted from the rack in a random position of the bag -> void Bag::addLetter(char letter)
			this->bag.addLetter(letter);
		}
	}
	//not here
	while (rack.getSize() < RACK_SIZE && this->bag.getSize() > 0) {
		rack.addLetter(this->bag.getLastLetter());
		// void Bag::removeLetter() -> bag.pop_back();
	}
	rack.sort();
}

void Game::showWinners()
{
	if (winnerPlayers.size() == 1) {
		cout << endl << "   " << bgGrey << winnerPlayers[0]->getColor() << "   " << winnerPlayers[0]->getName() << " WON!   " << dfltColor << endl;
	}
	else if (winnerPlayers.size() > 1) {
		cout << endl << "   " << "It's a tie! Winning players: " << endl;
		for (int i = 0; i < winnerPlayers.size(); i++) {
			cout << "   " << bgGrey << winnerPlayers[i]->getColor() << "   " << winnerPlayers[i]->getName() << "   " << dfltColor << endl;
		}
	}
}

vector<char> Game::checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected) {
	vector<char> possibleRack = rack.getRack();

	bool spaceExists = false; // dictates whether or not the word is new 
	int row = turn.getRow();
	int col = turn.getCol();

	for (int i = 0; i < turn.getWord().size(); i++) {
		// the cicle is broken if the word get's out of the board, overlaps with another word or there aren't enough letters to write it
		if (row == this->board.getNumRows() || col == this->board.getNumCols()) {
			// the word get's out of the board limits
			cout << "Your word doesn't fit on the board. You lost your turn.\n";
			validPosition = false;
			break;
		}
		if (turn.getWordLetter(i) != board.getLetter(row, col)) {
			// the char to be inserted is different from the one in the board
			if (board.getLetter(row, col) == ' ') {
				// the position is free to receive the char
				vector<char>::iterator pos = find(possibleRack.begin(), possibleRack.end(), turn.getWordLetter(i));
				if (pos != possibleRack.end()) {
					// the char to be inserted is on the rack
					spaceExists = true;
					possibleRack.erase(pos);
				}
				else {
					// the char isn't on the rack - invalid choice of word
					cout << "You don't have enough letters to write your word. You lost your turn.\n";
					validPosition = false;
					break;
				}
			}
			else {
				// the board already as another char on the position being tested - invalid placement of word
				cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
				validPosition = false;
				break;
			}
		}
		else {
			// the board already has the char being inserted - the word isn't isolated
			isConnected = true;
		}
		if (turn.getIsVertical())
			row++;
		else
			col++;
	}
	validPosition = (validPosition && spaceExists);
	return possibleRack;
}

bool Game::checkWordPlacement(const Turn& turn, Player& player, vector<int*>& changePlayer, bool& isConnected) {
	changePlayer.clear();
	string testWord;
	bool changeColor;
	int perpendicularIndex, paralelIndex;
	int initialParalelIndex, initialPerpendicularIndex;
	const int* parallelBoardSize;
	const int* perpendicularBoardSize;
	int* row;
	int* col;

	// initialize Indexes -> col is considered parallel to vertical and perpendicular to horizontal
	//                    -> row is considered perpendicular to vertical and parallel to horizontal
	if (turn.getIsVertical()) {
		initialPerpendicularIndex = turn.getRow();
		initialParalelIndex = turn.getCol();
		row = &perpendicularIndex;
		col = &paralelIndex;
		parallelBoardSize = &BOARD_COLS; //TODO: chamge this
		perpendicularBoardSize = &BOARD_ROWS;
	}
	else {
		initialParalelIndex = turn.getRow();
		initialPerpendicularIndex = turn.getCol();
		row = &paralelIndex;
		col = &perpendicularIndex;
		parallelBoardSize = &BOARD_ROWS; //TODO: chamge this
		perpendicularBoardSize = &BOARD_COLS;
	}


	paralelIndex = initialParalelIndex;
	perpendicularIndex = initialPerpendicularIndex;
	// get the word formed in the same direction as the played word
	testWord = getLine(perpendicularBoardSize, perpendicularIndex, row, col, turn.getWord(), changePlayer, true);
	if (!searchWord(this->dictionary, testWord)) {
		cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
		return false;
	}
	if (testWord.length() > turn.getWord().length())
		isConnected = true;

	for (int i = 0; i < turn.getWord().length(); i++) {
		perpendicularIndex = initialPerpendicularIndex + i;
		paralelIndex = initialParalelIndex;
		changeColor = board.getLetter(*row, *col) == ' ';

		string letter = { turn.getWordLetter(i) };
		// get the word formed by the letter i of the played word in its perpendicular direction
		testWord = getLine(parallelBoardSize, paralelIndex, row, col, letter, changePlayer, changeColor);
		if (testWord.length() > 1) {
			if (!searchWord(this->dictionary, testWord)) {
				cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
				return false;
			}
			isConnected = true;
		}
	}
	if (!isConnected)
		cout << "You inserted an isolated word. You lost your turn.\n";
	return true;
}

void Game::getHalfLine(const int* boardSize, int& index, int*& row, int*& col, string& testWord, vector<int*>& changePlayer, bool changeColor, int step) {
	while (index >= 0 && index < *boardSize && board.getLetter(*row, *col) != ' ') {
		testWord.push_back(board.getLetter(*row, *col));
		if (changeColor)
			changePlayer.push_back(this->board.getIdPointer(*row, *col));
		index += step;
	}
}
string Game::getLine(const int* boardSize, int& index, int*& row, int*& col, const string wordPart, vector<int*>& changePlayer, bool changeColor) {
	string testWord;
	index--;
	getHalfLine(boardSize, index, row, col, testWord, changePlayer, changeColor, -1);
	if (testWord.length() != 0)
		reverse(testWord.begin(), testWord.end());

	testWord += wordPart;

	index += testWord.length() + 1;
	getHalfLine(boardSize, index, row, col, testWord, changePlayer, changeColor, 1);
	return testWord;
}