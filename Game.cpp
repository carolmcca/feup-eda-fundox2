#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "Game.h"

using namespace std;

Game::Game(mt19937 generator) {

	string dictionaryPath;
	vector<Player> players;
	

	this->readConfig(dictionaryPath, generator);
	this->setDictionary(dictionaryPath);

	this->readNumPlayers();
	this->readNamePlayers();

	this->board.initBoard(BOARD_ROWS, BOARD_COLS);
	this->fillRack(true);
}

//-------------------------------------------------------------

void Game::readConfig(string& dictionaryPath, mt19937 generator) {

	ifstream extractFile(FILE_CONFIG);
	if (!extractFile.is_open()) {
		cout << "File CONFIG.txt not found!" << endl;
		exit(1);
	}
	extractFile.ignore(1000, ':');
	extractFile >> this->SCORE_MAX;
	extractFile.ignore(1000, ':');
	extractFile >> dictionaryPath;
	extractFile.ignore(1000, ':');
	char letter;
	int num_occurences;

	while (extractFile >> letter >> num_occurences)
		for (int i = 1; i <= num_occurences; i++)
			this->bag.addEndLetter(letter);
	this->bag.shuffle(generator);

	extractFile.close();
}

//-------------------------------------------------------------

void Game::readNumPlayers() {
	while (true) {
		cout << "Please insert the number of players (2-4): ";
		cin >> this->INITIAL_NUM_PLAYERS;
		if (isInputValid("cin") && this->INITIAL_NUM_PLAYERS >= 2 && this->INITIAL_NUM_PLAYERS <= 4) {
			this->numPlayers = this->INITIAL_NUM_PLAYERS;
			return;
		}
		cout << "The number must be an integer between 2 and 4!" << endl;
	}
}

//-------------------------------------------------------------

void Game::readNamePlayers() {
	for (int i = 0; i < this->INITIAL_NUM_PLAYERS; i++) {
		Player player(i);
		player.readName();
		players.insert(pair<int, Player> (i, player));
	}
}

//------------------------------------------------------

void Game::setDictionary(const string& dictionaryPath) {
	ifstream wordsFile;
	wordsFile.open(dictionaryPath);

	if (!wordsFile.is_open()) {
		cout << "Error! File '" << dictionaryPath << "' not found.\n";
		exit(1);
	}

	while (!wordsFile.eof()) {
		string entry;
		wordsFile >> entry;
		this->dictionary.insert(entry);
	}
	wordsFile.close();
}

//------------------------------------------------------

void Game::fillRack(bool restoreRack) {
	if (restoreRack) {
		while (this->rack.getSize() > 0) {
			char letter = this->rack.getFirstLetter();
			this->bag.addRandomLetter(letter);
		}
	}
	while (rack.getSize() < RACK_SIZE && this->bag.getSize() > 0) {
		rack.addLetter(this->bag.getLastLetter());
	}
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

	int gaveUpSize = this->INITIAL_NUM_PLAYERS - this->numPlayers;
	cout << setw(board.getNumCols() - players.size() + gaveUpSize + 1) << " ";
	for (map<int, Player>::const_iterator it = players.cbegin(); it != players.cend(); it++) {
		if (it->second.getGaveUp())
			cout << it->second.getColor() << setw(3) << it->second.getScore();
	}
	cout << dfltColor << endl;
}

//-------------------------------------------------------------

multiset<char> Game::checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected) {
	multiset<char> possibleRack = rack.getRack();

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
				multiset<char>::iterator it = possibleRack.find(turn.getWordLetter(i));
				if (it != possibleRack.end()) {
					// the char to be inserted is on the rack
					spaceExists = true;
					possibleRack.erase(it);
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

//-------------------------------------------------------------

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

	// for each letter of the word
	for (int i = 0; i < turn.getWord().length(); i++) {
		perpendicularIndex = initialPerpendicularIndex + i;
		paralelIndex = initialParalelIndex;
		changeColor = board.getLetter(*row, *col) == ' '; /// true if the position of the board is empty -> we are completing a word

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

//-------------------------------------------------------------

void Game::getHalfLine(const int* boardSize, int& index, int*& row, int*& col, string& testWord, vector<int*>& changePlayer, bool changeColor, int step) {
	while (index >= 0 && index < *boardSize && board.getLetter(*row, *col) != ' ') {
		testWord.push_back(board.getLetter(*row, *col));
		if (changeColor)
			changePlayer.push_back(this->board.getIdPointer(*row, *col));
		index += step;
	}
}

//-------------------------------------------------------------

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

//-------------------------------------------------------------

void Game::run() {
	bool isFirstWord = true;
	map<int, Player>::iterator playersIt = this->players.end()--;
	int passTurns = 0;
	int passRounds = 0;

	while (playersIt->second.getScore() < this->SCORE_MAX && passRounds < 3 && this->numPlayers > 1) {
		playersIt++;
		if (playersIt == players.end())
			playersIt = players.begin();

		if (playersIt->second.getGaveUp())
			continue;

		bool restoreRack = (passRounds > 0 && passTurns == 0);
		this->fillRack(restoreRack);
		this->showScores();
		this->board.show();
		this->rack.show(this->board.getNumCols());
		Turn turn;

		string message = playersIt->second.getColor() + playersIt->second.getName() + "'s turn" + dfltColor;
		TurnPlay input = turn.readWord(message, this->dictionary);
		switch (input) {
		case PASS:
			passRounds += (passTurns + 1) / numPlayers;
			passTurns = (passTurns + 1) % numPlayers;
			continue;
		case GIVEUP:
			this->numPlayers--;
			this->players.erase(playersIt);
			passRounds += passTurns / numPlayers;
			playersIt->second.setGaveUp(true);
			continue;
		case PLAY:
			passTurns = 0;
			passRounds = 0;
		}

		turn.readPosition();
		turn.readDirection();

		bool validPosition = true;
		bool isConnected = isFirstWord;
		multiset<char> possibleRack = checkExistingLetters(turn, validPosition, isConnected);
		if (validPosition && checkWordPlacement(turn, playersIt->second, changePlayer, isConnected) && isConnected) {
			isFirstWord = false;
			this->rack.setRack(possibleRack);
			updateBoard(turn, playersIt->first);
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

void Game::showWinners()
{
	if (winnerPlayers.size() == 1) {
		cout << "   " << bgGrey << winnerPlayers[0]->getColor() << "   " << winnerPlayers[0]->getName() << " WON!   " << dfltColor << endl;
	}
	else if (winnerPlayers.size() > 1) {
		cout << "   " << "It's a tie! Winning players: " << endl;
		for (int i = 0; i < winnerPlayers.size(); i++) {
			cout << "   " << bgGrey << winnerPlayers[i]->getColor() << "   " << winnerPlayers[i]->getName() << "   " << dfltColor << endl;
		}
	}
}

//-------------------------------------------------------------

void Game::updateBoard(const Turn &turn, int playerId) {
	for (int i = 0; i < turn.getWord().length(); i++) {
		pair<char, int> entry = pair<char, int>(turn.getWordLetter(i), playerId);
		if (turn.getIsVertical())
			board.setEntry(turn.getRow() + i, turn.getCol(), entry);
		else
			board.setEntry(turn.getRow(), turn.getCol() + i, entry);
	}
	for (int i = 0; i < changePlayer.size(); i++)
		*changePlayer[i] = playerId;
}

