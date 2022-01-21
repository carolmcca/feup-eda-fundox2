#include <iostream>
#include <string>
#include "Turn.h"

using namespace std;

/**
* @brief default constructor
*/
Turn::Turn() { }

//===========================================================

/**
	* @brief read the played word from the keyboard, until reaching the maximum number of attempts
	* @return an enum type referent to the nature of the input (pass, give up or play)
	*/
TurnPlay Turn::readWord(const string& message, const set<string>& dictionary) {
	cout << message << endl; // message: "PlayerX's turn"

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

//=======================================================================

/**
* @brief read the position of the played word (ROW column) from the keyboard, repeating endlessly until the input is valid
*/
void Turn::readPosition(const int BOARD_ROWS, const int BOARD_COLS) {
	char sep;
	string line;
	while (true) {
		cout << "Position of 1st letter (ROW column): ";
		getline(cin, line);
		if (isInputValid("getline") && line.size() == 3) {  // check if the input is in the correct format
			if (line[1] == ' ') {
				this->row = int(line[0] - 'A');
				this->col = int(line[2] - 'a');
				if (0 <= this->row && BOARD_ROWS > this->row && 0 <= this->col && BOARD_COLS > this->col)
					return;
				cout << "Error. Example of valid input:\nA b" << endl;
			}
		}
		else {
			cout << "Error. Example of valid input:\nA b" << endl;
		}
	}
}

//=======================================================================

/**
* @brief read the direction of the word (H / V) from the keyboard, repeating endlessly until the input is valid
*/
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

//========================================================

string Turn::getWord() const { return this->word; }

int Turn::getRow() const { return row; }

int Turn::getCol() const { return col; }

bool Turn::getIsVertical() const { return isVertical; }

//========================================================

/**
* @brief get the letter i from the string word
* @return char with the required letter
*/
char Turn::getWordLetter(int i) const { return this->word[i]; }


