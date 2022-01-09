#include "utils.h"

using namespace std;

const string dfltColor = "\033[0m";
const string bgGrey = "\033[47m";
const string red = "\033[31m";
const string blue = "\033[34m";
const string green = "\033[92m";
const string magenta = "\033[95m";
const string black = "\033[30m";
const vector<string> colors = { red, blue, green, magenta };

const int NUM_MAX_ATTEMPTS = 3;
const int BOARD_SIZE = 13;
const string FILE_CONFIG = "CONFIG.txt";

bool searchWord(const set<string>& dictionary, string word) {
	for (int i = 0; i < word.length(); i++)
		word[i] = tolower(word[i]);

	return dictionary.find(word) != dictionary.end();
}