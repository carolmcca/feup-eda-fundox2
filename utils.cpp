#include "utils.h"

using namespace std;

bool searchWord(const set<string>& dictionary, string word) {
	for (int i = 0; i < word.length(); i++)
		word[i] = tolower(word[i]);

	return dictionary.find(word) != dictionary.end();
}