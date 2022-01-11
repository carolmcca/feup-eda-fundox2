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
#include <set>

using namespace std;

// set colors


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

	srand(time(NULL));
	random_device rd;
	mt19937 generator(rd());

	int SCORE_MAX;
	string dictionaryPath;
	vector<char> bagVector;
	set<string> dictionary;
	readConfig(SCORE_MAX, dictionaryPath, bagVector);
	setDictionary(dictionary, dictionaryPath);

	int INITIAL_NUM_PLAYERS;
	readNumPlayers(INITIAL_NUM_PLAYERS);

	string name;
	vector<Player> players;
	for (int i = 0; i < INITIAL_NUM_PLAYERS; i++) {
		readNamePlayer(name, i);
		Player player(name, i);
		players.push_back(player);
	}

	Bag bag(bagVector, generator);
	Board board(BOARD_SIZE);
	Game game(bag, board, players, SCORE_MAX, dictionary);
	
	game.run();
	game.setWinnerPlayers();
	game.showWinners();

	return 0;
}
