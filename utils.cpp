#include "utils.h"
#include <iostream>

using namespace std;

// TODO mudar nome para isValidInput
bool valid(const string& inputType, const string errorMessage, const char terminator) {
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

bool searchWord(const set<string>& dictionary, string word) {
	for (int i = 0; i < word.length(); i++)
		word[i] = tolower(word[i]);

	return dictionary.find(word) != dictionary.end();
}