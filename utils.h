#pragma once
#include <set>
#include <string>
#include <vector>

const std::string dfltColor = "\033[0m";
const std::string bgGrey = "\033[47m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string green = "\033[92m";
const std::string magenta = "\033[95m";
const std::string black = "\033[30m";
const std::vector<std::string> colors = { red, blue, green, magenta };

const int NUM_MAX_ATTEMPTS = 3;
const int BOARD_ROWS = 10;
const int BOARD_COLS = 15;
const int RACK_SIZE = 7;
const std::string FILE_CONFIG = "CONFIG.txt";

bool searchWord(const std::set<std::string>& dictionary, std::string word);

bool isInputValid(const std::string& inputType, const std::string errorMessage = "", const char terminator = '\n');

void wordToUpper(std::string& word);
void wordToLower(std::string& word);