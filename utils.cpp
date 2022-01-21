#include "utils.h"
#include <iostream>

using namespace std;

/**
* @brief check if the input stream is OK
* @return true if the input is of the expected type and false otherwise
*/
bool isInputValid(const string& inputType, const string errorMessage, const char terminator) {
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

//================================================================

/**
* @brief search for the word on a set dictionary
* @return true if the word is on the set and false otherwise
*/
bool searchWord(const set<string>& dictionary, string word) {
	wordToLower(word);
	return dictionary.find(word) != dictionary.end();
}

//================================================================

/**
* @brief change all the letters of the word to lowercase
*/
void wordToLower(string &word) {
	for (int i = 0; i < word.size(); i++)
		word[i] = tolower(word[i]);
}

//================================================================

/**
* @brief change all the letters of the word to uppercase
*/
void wordToUpper(string &word) {
	for (int i = 0; i < word.size(); i++)
		word[i] = toupper(word[i]);
}