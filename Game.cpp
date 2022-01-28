#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "Game.h"

using namespace std;

/**
* @brief construct the game - read and save all the game's configurations
*							- read the number of players and their names from the keyboard
*							- initialize the board
*							- create the first rack to be used in the game
*/
Game::Game(mt19937 generator) {

	string dictionaryPath;
	vector<Player> players;


	this->readConfig(dictionaryPath, generator);
	this->setDictionary(dictionaryPath);

	this->readNumPlayers();
	this->readNamePlayers();
}

//================================================================

/**
* @brief read and save all the game's configurations
*		 create the bag based on the number of occurences of each letter defined on the configFile
*		 shuffle the bag
*		 create the rack based on its predefined size (configFile)
*/
void Game::readConfig(string& dictionaryPath, mt19937 generator) {
	cout << "Choose the duration of the game (this will influence the configurations):" << endl;
	cout << "0 - Standard; 1 - Short; 2 - Intermediate; 3 - Long" << endl;
	string configFileNum;
	cin >> configFileNum;
	string configFile = "CONFIG_" + configFileNum + ".txt";

	ifstream extractFile(configFile);
	if (!extractFile.is_open()) {
		cout << "File " << configFile << " not found!" << endl;
		exit(1);
	}
	int boardRows, boardCols, rackSize;

	extractFile.ignore(1000, ':');
	extractFile >> this->SCORE_MAX;
	extractFile.ignore(1000, ':');
	extractFile >> boardRows;
	extractFile.ignore(1000, ':');
	extractFile >> boardCols;
	extractFile.ignore(1000, ':');
	extractFile >> rackSize;
	extractFile.ignore(1000, ':');
	extractFile >> dictionaryPath;
	extractFile.ignore(1000, ':');
	char letter;
	int num_occurences;

	this->board.initBoard(boardRows, boardCols);
	this->rack.setMaxSize(rackSize);
	this->fillRack(true);

	// fill the bag with letters extraxted from configFile
	while (extractFile >> letter >> num_occurences)
		for (int i = 1; i <= num_occurences; i++)
			this->bag.addEndLetter(letter);
	this->bag.shuffle(generator);

	extractFile.close();
}

//================================================================

/**
* @brief read the number of players from the keyboard, repeating endlessly until the input is valid
*/
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

//================================================================

/**
* @brief read the name of the players from the keyboard, repeating endlessly until the input is valid
*		 (default name: PlayerX, being X the number of the player)
*/
void Game::readNamePlayers() {
	for (int i = 0; i < this->INITIAL_NUM_PLAYERS; i++) {
		Player player(i);
		player.readName();
		players.push_back(player);
	}
}

//================================================================

/**
* @brief define the used dictionary - extract the list of valid words to a set
*/
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

//================================================================

/**
* @brief define the rack - empty the rack to the bag if the rack needs to be restored
*		 extract letters from the bag until the rack has rackSize letters
*/
void Game::fillRack(bool restoreRack) {
	if (restoreRack) {
		while (this->rack.getSize() > 0) {
			char letter = this->rack.getFirstLetter();
			this->bag.randomlyAddLetter(letter);
		}
	}
	while (rack.getSize() < rack.getMaxSize() && this->bag.getSize() > 0) {
		rack.addLetter(this->bag.getLastLetter());
	}
}

//================================================================

/**
* @brief update the scores - reset all players' scores
*		 search throught the board and, when a letter is found, add one point to the score of the corresponding player
*/
void Game::updateScores() {
	for (int i = 0; i < players.size(); i++)
		players[i].resetScore();

	for (int i = 0; i < board.getNumRows(); i++)
		for (int j = 0; j < board.getNumCols(); j++)
			if (board.getId(i, j) != -1)
				for (int k = 0; k < numPlayers; k++)
					if (players[k].getId() == board.getId(i, j))
						players[k].incScore();
}

//================================================================

/**
 * @brief display the players' scores
 */
void Game::showScores() const {
	cout << endl << setw(board.getNumCols() - 2) << " ";
	cout << "SCORE BOARD" << endl;

	int gaveUpSize = INITIAL_NUM_PLAYERS - numPlayers;
	cout << setw(board.getNumCols() - players.size() + gaveUpSize + 1) << " ";
	for (int i = 0; i < players.size(); i++)
		cout << players[i].getColor() << setw(3) << players[i].getScore();
	cout << dfltColor << endl;
}

//================================================================

/**
* @brief update the board - add the letters of the played word to the board in the correct position
*		 assign each letter stolen from another player to the current player
*/
void Game::updateBoard(const Turn& turn, int playerId) {
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

//================================================================

/**
* @brief check if the word uses letters of another word and if each letter can be placed in the indicated position, that is, if the word:
*               - doesn't get out of the board limits
*			    - doesn't overlap inconsistently with another one
*				- isn't already written in the specified position
*			    - is writable with the available letters
* @return rack without the letters that can be inserted on the board
*/
multiset<char> Game::checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected) {
	multiset<char> possibleRack = rack.getRack();

	bool spaceExists = false; // dictates whether or not the word is new 
	int row = turn.getRow();
	int col = turn.getCol();

	for (int i = 0; i < turn.getWord().size(); i++) {
		// the cicle is broken if the word gets out of the board, overlaps with another word or there aren't enough letters to write it
		if (row == this->board.getNumRows() || col == this->board.getNumCols()) {
			// the word gets out of the board limits
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

//================================================================

/**
 * @brief check the word formed in the same direction and all the words formed in the perpendicular direction to the played word
 *		  check whether or not the word continues through another on the board (isConnected)
 * @return true if all the formed words are on the dictionary and false otherwise
 */
bool Game::checkWordPlacement(const Turn& turn, Player& player, vector<int*>& changePlayer, bool& isConnected) {
	changePlayer.clear();

	string testWord;
	bool changeColor;
	int perpendicularIndex, paralelIndex;
	int initialParalelIndex, initialPerpendicularIndex;
	int BOARD_COLS = this->board.getNumCols();
	int BOARD_ROWS = this->board.getNumRows();

	int* row;
	int* col;
	const int* parallelBoardSize;
	const int* perpendicularBoardSize;
	
	// initialize Indexes -> col is considered parallel to vertical and perpendicular to horizontal
	//                    -> row is considered perpendicular to vertical and parallel to horizontal
	if (turn.getIsVertical()) {
		initialPerpendicularIndex = turn.getRow();
		initialParalelIndex = turn.getCol();
		row = &perpendicularIndex;
		col = &paralelIndex;
		parallelBoardSize = &BOARD_COLS;
		perpendicularBoardSize = &BOARD_ROWS;
	}
	else {
		initialParalelIndex = turn.getRow();
		initialPerpendicularIndex = turn.getCol();
		row = &paralelIndex;
		col = &perpendicularIndex;
		parallelBoardSize = &BOARD_ROWS;
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
		changeColor = board.getLetter(*row, *col) == ' '; // true if the position of the board is empty - we are completing a word

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

//================================================================

/**
 * @brief append to testWord the neighbor chars of (row, col) in the direction indicated by step (-1 to the left, +1 to the right)
 */
void Game::getHalfLine(const int* boardSize, int& index, int*& row, int*& col, string& testWord, vector<int*>& changePlayer, bool changeColor, int step) {
	while (index >= 0 && index < *boardSize && board.getLetter(*row, *col) != ' ') {
		testWord.push_back(board.getLetter(*row, *col));
		if (changeColor)
			changePlayer.push_back(this->board.getIdPointer(*row, *col));
		index += step;
	}
}

//================================================================

/**
 * @brief create a string (testWord) containing the word formed with the placement of the new char in (*row *col)
 *		  the analisys direction is indirectly defined through the parameter index (indicates the direction through which the board is iterated)
 * 		  i.e. if the prependicularIndex is passed, the direction of testWord will be the same of the played word
 * @return string testWord
 */
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

//================================================================

/**
 * @brief run the game
 *				ask the current player for their move, analising if it is valid:
 *						- if it is, updates the rack, the bag, the board and the score table
 *						- if it isn't, asks the user to try again or considers that they passed, depending on the failed validity condition
 *				in order to know when to end the game (end of the while cycle) keep track of:
 *						- the score table
 *						- the number of consecutive rounds that everyone passed
 *						- the number of players who are still playing
 *				show the score table and the final board when the game ends
 */
void Game::run() {

	bool isFirstWord = true;
	int current = 0;
	int passTurns = 0;
	int passRounds = 0;
	while (this->players[(current-1+numPlayers) % numPlayers].getScore() < this->SCORE_MAX && passRounds < 3 && this->numPlayers > 1) {
		bool restoreRack = (passRounds > 0 && passTurns == 0);
		this->fillRack(restoreRack);
		this->showScores();
		this->board.show();
		this->rack.show(this->board.getNumCols());
		Turn turn;

		string message = players[current].getColor() + players[current].getName() + "'s turn" + dfltColor;
		TurnPlay input = turn.readWord(message, this->dictionary);
		switch (input) {
		case PASS:
			passRounds += (passTurns + 1) / numPlayers;
			passTurns = (passTurns + 1) % numPlayers;
			current = (current + 1) % this->numPlayers;
			continue;
		case GIVEUP:
			this->numPlayers--;
			players.erase(players.begin() + current);
			passRounds += passTurns / numPlayers;
			current = current % this->numPlayers;
			continue;
		case PLAY:
			passTurns = 0;
			passRounds = 0;
		}

		turn.readPosition(this->board.getNumRows(), this->board.getNumCols());
		turn.readDirection();

		bool validPosition = true;
		bool isConnected = isFirstWord;
		multiset<char> possibleRack = checkExistingLetters(turn, validPosition, isConnected);
		if (validPosition && checkWordPlacement(turn, players[current], changePlayer, isConnected) && isConnected) {
			isFirstWord = false;
			this->rack.setRack(possibleRack);
			updateBoard(turn, players[current].getId());
			updateScores();
		}
		else {
			passTurns++;
		}
		current = (current + 1) % this->numPlayers;
	}
	showScores();
	this->board.show();
}

//================================================================

/**
 * @brief determine who won the game, comparing the remaining players' scores
 */
void Game::setWinnerPlayers() {
	int numWinners = 0;
	int maxScore = -1;
	for (int i = 0; i < players.size(); i++) {
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

//================================================================

/**
 * @brief display the winner's name (or winners' names)
 *		  each name is presented with the color of the respective winner
 */
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