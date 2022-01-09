#include "fundox.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <random>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include "Player.h"
#include "Board.h"

using namespace std;

// set colors
const std::string dfltColor = "\033[0m";
const std::string bgGrey = "\033[47m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string green = "\033[92m";
const std::string magenta = "\033[95m";
const std::string black = "\033[30m";
const vector<string> colors = { red, blue, green, magenta };

const int NUM_MAX_ATTEMPTS = 3;
const int BOARD_SIZE = 13;

void readConfig(int& scoreMax, string& dictionaryPath, vector<char>& bag) { //fora

	ifstream extractFile("CONFIG.txt");
	if (!extractFile.is_open()) {
		cout << "File CONFIG.txt not found!" << endl;
		exit(1);
	}
	extractFile.ignore(1000, ':');
	extractFile >> scoreMax;
	extractFile.ignore(1000, ':');
	extractFile >> dictionaryPath;
	extractFile.ignore(1000, ':');
	setBag(extractFile, bag);
}

void setBag(ifstream& extractFile, vector<char>& bag) {
	char letter;
	int num_occurences;

	while (extractFile >> letter >> num_occurences)
		for (int i = 1; i <= num_occurences; i++)
			bag.push_back(letter);

	srand(time(NULL));
	random_device rd;
	mt19937 g(rd());

	shuffle(bag.begin(), bag.end(), g);
}

void setRack(vector<char>& bag, vector<char>& rack, bool restore) {
	if (restore) {
		while (!rack.empty()) {
			char letter = *rack.rbegin();
			rack.pop_back();
			// insert the letter extracted from the rack in a random position of the bag
			bag.insert(bag.begin() + (rand() % bag.size()), letter);
		}
	}

	while (rack.size() < 7 && !bag.empty()) {
		rack.push_back(*bag.rbegin());
		bag.pop_back();
	}
	sort(rack.begin(), rack.end());
}
void showRack(const vector<char>& rack) {
	cout << endl;
	for (int i = 0; i < BOARD_SIZE + 3 - rack.size(); i++)
		cout << " ";
	cout << bgGrey << black << " ";
	for (int i = 0; i < rack.size(); i++)
		cout << rack[i] << " ";
	cout << dfltColor << endl << endl;
}

bool valid(const string& inputType, const string errorMessage = "", const char terminator = '\n') {
	if (cin.fail()) {
		if (cin.eof()) {
			cin.clear();
		}
		else {
			cin.clear();
			cin.ignore(1000, terminator);
		}
	}
	else if (inputType == "cin") {
		bool correctTerminator = cin.peek() == terminator;
		cin.ignore(10000, terminator);
		if (correctTerminator)
			return true;
	}
	else {
		return true;
	}
	cout << errorMessage;
	return false;
}
bool searchWord(const string& path, string word) {
	bool found = false;
	ifstream wordsFile;
	wordsFile.open(path);

	if (!wordsFile.is_open()) {
		cout << "Error! File '" << path << "' not found.\n";
		exit(1);
	}

	for (int i = 0; i < word.length(); i++)
		word[i] = tolower(word[i]);

	while (!wordsFile.eof() && !found) {
		string entry;
		wordsFile >> entry;
		if (entry == word)
			found = true;
	}
	wordsFile.close();

	return found;
}

void readNumPlayers(int& numPlayers) {
	while (true) {
		cout << "Please insert the number of players (2-4): ";
		cin >> numPlayers;
		if (valid("cin") && numPlayers >= 2 && numPlayers <= 4)
			return;
		cout << "The number must be an integer between 2 and 4!" << endl;
	}
}
void readNamePlayer(vector<Player>& players, const int& index) { //sem classe (?) por a retornar a string e alteramos depois aonstruindo o player ao mesmo tempo?
	string name;
	while (true) {
		cout << colors[index] << "Player " << index + 1 << ": ";
		getline(cin, name);
		players[index].setName(name);
		cout << dfltColor;
		if (valid("getline", "Please insert a valid name\n")) {
			if (players[index].name.size() == 0) {
				cout << "Your name will be Player" << index + 1 << endl;
				players[index].name = "Player" + to_string(index + 1);
			}
			return;
		}
	}
}

TurnPlay readWord(string& word, const Player& player, const string& dictionary) {
	cout << player.color << player.name << "'s turn" << dfltColor << endl;
	int attempts = 0;
	while (attempts < NUM_MAX_ATTEMPTS) {
		cout << "Word: ";
		cin >> word;
		if (!valid("cin", "Please insert a valid word.\n")) {
			attempts++;
		}
		else {
			if (word == "P" || word == "p") {
				return PASS;
			}
			else if (word == "G" || word == "g") {
				return GIVEUP;
			}
			else {
				if (!searchWord(dictionary, word)) {
					attempts++;
					cout << "The inserted word isn't in the dictionary, please insert a valid word.\n";
				}
				else {
					return PLAY;
				}
			}
		}
	}
	cout << "Maximum number of attempts reached. You lost your turn!\n";
	return PASS;
}
void readDirection(Turn& turn) {
	char direction;
	while (true) {
		cout << "Direction (H / V) : ";
		cin >> direction;
		if (valid("cin")) {
			if (direction == 'v' || direction == 'V') {
				turn.isVertical = true;
				return;
			}
			else if (direction == 'h' || direction == 'H') {
				turn.isVertical = false;
				return;
			}
		}
		cout << "The input must be H/h for horizontal or V/v for vertical!\n";
	}
}
void readPosition(Turn& turn) {
	char sep;
	string line;
	while (true) {
		cout << "Position of 1st letter (ROW column): ";
		getline(cin, line);
		if (valid("getline") && line.size() == 3) {
			if (line[1] == ' ') {
				turn.row = int(line[0] - 'A');
				turn.col = int(line[2] - 'a');
				if (0 <= turn.row && BOARD_SIZE > turn.row && 0 <= turn.col && BOARD_SIZE > turn.col)
					return;
				cout << "Error. Example of valid input:\nA b" << endl;
			}
		}
		else {
			cout << "Error. Example of valid input:\nA b" << endl;
		}
	}
}

vector<char> checkExistingLetters(const board_t& board, Turn& turn, vector<char> rack, bool& validPosition, bool& isConnected) {
	bool spaceExists = false; // dictates whether or not the word is new 
	int row = turn.row;
	int col = turn.col;

	for (int i = 0; i < turn.word.size(); i++)
		turn.word[i] = toupper(turn.word[i]);

	for (int i = 0; i < turn.word.size(); i++) {
		// the cicle is broken if the word get's out of the board, overlaps with another word or there aren't enough letters to write it
		if (turn.row == BOARD_SIZE || turn.col == BOARD_SIZE) {
			// the word get's out of the board limits
			cout << "Your word doesn't fit on the board. You lost your turn.\n";
			validPosition = false;
			break;
		}

		if (turn.word[i] != board[row][col].first) {
			// the char to be inserted is different from the one in the board
			if (board[row][col].first == ' ') {
				// the position is free to receive the char
				vector<char>::iterator pos = find(rack.begin(), rack.end(), turn.word[i]);
				if (pos != rack.end()) {
					// the char to be inserted is on the rack
					spaceExists = true;
					rack.erase(pos);
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
		if (turn.isVertical)
			row++;
		else
			col++;
	}
	validPosition = (validPosition && spaceExists);
	return rack;
}

void getHalfLine(int& index, int*& row, int*& col, board_t& board, string& testWord, vector<Player**>& changePlayer, bool changeColor, int step) {
	while (index >= 0 && index < BOARD_SIZE && board[*row][*col].first != ' ') {
		testWord.push_back(board[*row][*col].first);
		if (changeColor)
			changePlayer.push_back(&(board[*row][*col].second));
		index += step;
	}
}
string getLine(int& index, int*& row, int*& col, board_t& board, const string wordPart, vector<Player**>& changePlayer, bool changeColor) {
	string testWord;
	index--;
	getHalfLine(index, row, col, board, testWord, changePlayer, changeColor, -1);
	if (testWord.length() != 0)
		reverse(testWord.begin(), testWord.end());

	testWord += wordPart;

	index += testWord.length() + 1;
	getHalfLine(index, row, col, board, testWord, changePlayer, changeColor, 1);
	return testWord;
}

bool checkWordPlacement(board_t& board, const Turn& turn, const string path, Player& player, vector<Player**>& changePlayer, bool& isConnected) {
	changePlayer.clear();
	string testWord;
	bool changeColor;
	int perpendicularIndex, paralelIndex;
	int initialParalelIndex, initialPerpendicularIndex;
	int* row;
	int* col;

	// initialize Indexes -> col is considered parallel to vertical and perpendicular to horizontal
	//                    -> row is considered perpendicular to vertical and parallel to horizontal
	if (turn.isVertical) {
		initialPerpendicularIndex = turn.row;
		initialParalelIndex = turn.col;
		row = &perpendicularIndex;
		col = &paralelIndex;
	}
	else {
		initialParalelIndex = turn.row;
		initialPerpendicularIndex = turn.col;
		row = &paralelIndex;
		col = &perpendicularIndex;
	}


	paralelIndex = initialParalelIndex;
	perpendicularIndex = initialPerpendicularIndex;
	// get the word formed in the same direction as the played word
	testWord = getLine(perpendicularIndex, row, col, board, turn.word, changePlayer, true);
	if (!searchWord(path, testWord)) {
		cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
		return false;
	}
	if (testWord.length() > turn.word.length())
		isConnected = true;

	for (int i = 0; i < turn.word.length(); i++) {
		perpendicularIndex = initialPerpendicularIndex + i;
		paralelIndex = initialParalelIndex;
		changeColor = board[*row][*col].first == ' ';

		string letter = { turn.word[i] };
		// get the word formed by the letter i of the played word in its perpendicular direction
		testWord = getLine(paralelIndex, row, col, board, letter, changePlayer, changeColor);
		if (testWord.length() > 1) {
			if (!searchWord(path, testWord)) {
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

void updateScores(const board_t& board, vector<Player>& players) {
	for (int i = 0; i < players.size(); i++)
		players[i].score = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].second != nullptr)
				board[i][j].second->score++;
		}
	}
}
void showScores(const vector<Player>& players) {
	cout << endl << setw(BOARD_SIZE - 2) << " ";
	cout << "SCORE BOARD" << endl;
	int gaveUpSize = std::count_if(players.begin(), players.end(), [](const Player& p) { return p.gaveUp; });
	cout << setw(BOARD_SIZE - players.size() + gaveUpSize + 1) << " ";
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].gaveUp)
			cout << players[i].color << setw(3) << players[i].score;
	}
	cout << dfltColor << endl;
}



int main() {
	board_t board(BOARD_SIZE, vector<pair<char, Player*>>(BOARD_SIZE));
	vector<char> bag;
	vector<char> rack, possibleRack;
	vector<Player> players;
	int INITIAL_NUM_PLAYERS, numPlayers;
	int SCORE_MAX;
	string dictionaryPath;
	vector<Player**> changePlayer;
	bool isFirstWord = true;

	readConfig(SCORE_MAX, dictionaryPath, bag);

	Board board;

	readNumPlayers(INITIAL_NUM_PLAYERS);
	players.resize(INITIAL_NUM_PLAYERS);

	for (int i = 0; i < INITIAL_NUM_PLAYERS; i++) {
		readNamePlayer(players, i);
		players[i].setColor(colors[i]);
	}

	numPlayers = INITIAL_NUM_PLAYERS;
	int current = numPlayers - 1;
	int passTurns = 0, passRounds = 0;
	Turn turn;
	while (players[current].score < SCORE_MAX && passRounds < 3 && numPlayers > 1) {
		current = (current + 1) % INITIAL_NUM_PLAYERS;

		if (!players[current].gaveUp) {
			bool restoreRack = (passRounds > 0 && passTurns == 0);
			setRack(bag, rack, restoreRack);
			showScores(players);
			board.show();
			showRack(rack);

			TurnPlay input = readWord(turn.word, players[current], dictionaryPath);
			switch (input) {
			case PASS:
				passRounds += (passTurns + 1) / numPlayers;
				passTurns = (passTurns + 1) % numPlayers;
				continue;
			case GIVEUP:
				numPlayers--;
				passRounds += passTurns / numPlayers;
				players[current].gaveUp = true;
				continue;
			case PLAY:
				passTurns = 0;
				passRounds = 0;
			}
			readPosition(turn);
			readDirection(turn);

			bool validPosition = true;
			bool isConnected = isFirstWord;
			possibleRack = checkExistingLetters(board, turn, rack, validPosition, isConnected);
			if (validPosition && checkWordPlacement(board, turn, dictionaryPath, players[current], changePlayer, isConnected) && isConnected) {
				isFirstWord = false;
				rack = possibleRack;
				for (int i = 0; i < turn.word.length(); i++) {
					pair<char, Player*> entry = pair<char, Player*>(toupper(turn.word[i]), &players[current]);
					if (turn.isVertical)
						board.setEntry(turn.row + i, turn.col, entry);
					else
						board.setEntry(turn.row, turn.col + i, entry);
				}
				for (int i = 0; i < changePlayer.size(); i++)
					*changePlayer[i] = &players[current];

				updateScores(board, players);
			}
			else {
				passTurns++;
			}
		}
	}

	showScores(players);
	board.show();

	int numWinners = 0;
	int maxScore = -1;
	vector<Player*> winnerPlayers;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].gaveUp) {
			if (players[i].score > maxScore) {
				winnerPlayers.clear();
				winnerPlayers.push_back(&players[i]);
				maxScore = players[i].score;
			}
			else if (players[i].score == maxScore) {
				winnerPlayers.push_back(&players[i]);
			}
		}
	}

	if (winnerPlayers.size() == 1) {
		cout << endl << "   " << bgGrey << winnerPlayers[0]->color << "   " << winnerPlayers[0]->name << " WON!   " << dfltColor << endl;
	}
	else if (winnerPlayers.size() > 1) {
		cout << endl << "   " << "It's a tie! Winning players: " << endl;
		for (int i = 0; i < winnerPlayers.size(); i++) {
			cout << "   " << bgGrey << winnerPlayers[i]->color << "   " << winnerPlayers[i]->name << "   " << dfltColor << endl;
		}
	}

	return 0;
}
