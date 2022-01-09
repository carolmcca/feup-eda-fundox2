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
#include <set>

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
const string FILE_CONFIG = "CONFIG.txt";

void readConfig(int& scoreMax, string& dictionaryPath, vector<char>& bag) { 

	ifstream extractFile(FILE_CONFIG);
	if (!extractFile.is_open()) {
		cout << "File CONFIG.txt not found!" << endl;
		exit(1);
	}
	extractFile.ignore(1000, ':');
	extractFile >> scoreMax;
	extractFile.ignore(1000, ':');
	extractFile >> dictionaryPath;
	extractFile.ignore(1000, ':');
	char letter;
	int num_occurences;

	while (extractFile >> letter >> num_occurences)
		for (int i = 1; i <= num_occurences; i++)
			bag.push_back(letter);
	
	extractFile.close();
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

// TODO mudar nome para isValidInput
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


void readNumPlayers(int& numPlayers) {
	while (true) {
		cout << "Please insert the number of players (2-4): ";
		cin >> numPlayers;
		if (valid("cin") && numPlayers >= 2 && numPlayers <= 4)
			return;
		cout << "The number must be an integer between 2 and 4!" << endl;
	}
}
void readNamePlayer(string& name, const int& index) { //sem classe (?) por a retornar a string e alteramos depois aonstruindo o player ao mesmo tempo?
	while (true) {
		cout << colors[index] << "Player " << index + 1 << ": ";
		getline(cin, name);
		cout << dfltColor;
		if (valid("getline", "Please insert a valid name\n")) {
			if (name.size() == 0) {
				cout << "Your name will be Player" << index + 1 << endl;
				name = "Player" + to_string(index + 1);
			}
			return;
		}
	}
}



void setDictionary(set<string>& dictionary, const string& path) {
	ifstream wordsFile;
	wordsFile.open(path);

	if (!wordsFile.is_open()) {
		cout << "Error! File '" << path << "' not found.\n";
		exit(1);
	}

	while (!wordsFile.eof()) {
		string entry;
		wordsFile >> entry;
		dictionary.insert(entry);
	}
	wordsFile.close();
}


int main() {
	vector<char> bag;
	vector<char> rack, possibleRack;
	vector<Player> players;
	int INITIAL_NUM_PLAYERS, numPlayers;
	int SCORE_MAX;
	string dictionaryPath;
	vector<Player**> changePlayer;
	bool isFirstWord = true;
	set<string> dictionary;
	setDictionary(dictionary);


	readConfig(SCORE_MAX, dictionaryPath, bag);

	Board board(BOARD_SIZE);

	string name;
	readNumPlayers(INITIAL_NUM_PLAYERS);
	for (int i = 0; i < INITIAL_NUM_PLAYERS; i++) {
		readNamePlayer(name, i);
		Player player(name, colors[i]);
		players.push_back(player);
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
