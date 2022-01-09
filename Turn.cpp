#include "Turn.h"
#include <iostream>
#include <string>

using namespace std;

TurnPlay Turn::readWord(const string& message, const string& dictionary) {
	cout << message << endl;
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

void Turn::readDirection() {
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
void Turn::readPosition() {
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

void Turn::wordToUpper() {
  for (int i = 0; i < this->word.size(); i++)
    this->word[i] = toupper(this->word[i]);
}