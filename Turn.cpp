#include "Turn.h"
#include <iostream>
#include <string>

using namespace std;

TurnPlay Turn::readWord(const string& message, const set<string>& dictionary) {
	cout << message << endl;
	int attempts = 0;
	string word;
	while (attempts < NUM_MAX_ATTEMPTS) {
		cout << "Word: ";
		cin >> word;
		wordToUpper(word);
		if (!isInputValid("cin", "Please insert a valid word.\n")) {
			attempts++;
		}
		else {
			if (word == "P") {
				return PASS;
			}
			else if (word == "G") {
				return GIVEUP;
			}
			else {
				if (!searchWord(dictionary, word)) {
					attempts++;
					cout << "The inserted word isn't in the dictionary, please insert a valid word.\n";
				}
				else {
					this->word = word;
					return PLAY;
				}
			}
		}
	}
	cout << "Maximum number of attempts reached. You lost your turn!\n";
	return PASS;
}

//------------------------------------------------------------------------------------------------

void Turn::readDirection() {
	char direction;
	while (true) {
		cout << "Direction (H / V) : ";
		cin >> direction;
		direction = toupper(direction);
		if (isInputValid("cin")) {
			if (direction == 'V') {
				this->isVertical = true;
				return;
			}
			else if (direction == 'H') {
				this->isVertical = false;
				return;
			}
		}
		cout << "The input must be H/h for horizontal or V/v for vertical!\n";
	}
}
void Turn::readPosition() {
	char sep;
	string line;
	while (true) {
		cout << "Position of 1st letter (ROW column): ";
		getline(cin, line);
		if (isInputValid("getline") && line.size() == 3) {
			if (line[1] == ' ') {
				this->row = int(line[0] - 'A');
				this->col = int(line[2] - 'a');
				if (0 <= this->row && BOARD_SIZE > this->row && 0 <= this->col && BOARD_SIZE > this->col)
					return;
				cout << "Error. Example of valid input:\nA b" << endl;
			}
		}
		else {
			cout << "Error. Example of valid input:\nA b" << endl;
		}
	}
}


Turn::Turn() {
	
}

char Turn::getWordLetter(int i) const {
	return this->word[i];
}

string Turn::getWord() const {
	return this->word;
}

int Turn::getRow() const {
	return row;
}

int Turn::getCol() const {
	return col;
}

bool Turn::getIsVertical() const {
	return isVertical;
}