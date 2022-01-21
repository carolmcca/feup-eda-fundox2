#pragma once
#include <set>
#include <string>
#include <vector>

//set colors
const std::string dfltColor = "\033[0m";
const std::string bgGrey = "\033[47m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string green = "\033[92m";
const std::string magenta = "\033[95m";
const std::string black = "\033[30m";
const std::vector<std::string> colors = { red, blue, green, magenta };

const int NUM_MAX_ATTEMPTS = 3; /// maximum number of times that a player can insert a word that isn't on the dictionary
const int BOARD_ROWS = 10; /// number of board rows
const int BOARD_COLS = 15; /// number of board columns
const int RACK_SIZE = 7; /// maximum size of the rack
const std::string FILE_CONFIG = "CONFIG.txt"; /// name of the text file containing configuration parameters

bool searchWord(const std::set<std::string>& dictionary, std::string word);

bool isInputValid(const std::string& inputType, const std::string errorMessage = "", const char terminator = '\n');

void wordToUpper(std::string& word);
void wordToLower(std::string& word);