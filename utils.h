#include <set>
#include <string>
#include <vector>

const std::string dfltColor;
const std::string bgGrey;
const std::string red;
const std::string blue;
const std::string green;
const std::string magenta;
const std::string black;
const vector<string> colors;

const int NUM_MAX_ATTEMPTS;
const int BOARD_SIZE;
const string FILE_CONFIG;

bool searchWord(const std::set<std::string>& dictionary, std::string word);
