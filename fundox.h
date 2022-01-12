#pragma once
#include <vector>
#include <string>
#include <set>
#include "Player.h"
#include "Board.h"
#include "Bag.h"
#include "Rack.h"
#include "Turn.h"
#include "Game.h"
#include "utils.h"

/**
 * @brief Extract the winning score, the dictionary's path and the letters of the bag from the file FILE_CONFIG
 */
void readConfig(int& scoreMax, std::string& dictionaryPath, std::vector<char>& bag);

/**
* @brief Read the number of players from the keyboard, repeating endlessly until the input is valid
*/
void readNumPlayers(int& numPlayers);

/**
* @brief Read the name of a player from the keyboard to the string name, repeating endlessly until the input is valid
*		 (default name (if the user introduces new line): PlayerX, being X the number of the player)
*/
void readNamePlayer(std::string& name, const int& index);

/* 
* @brief Extract the words from file dictionaryPath to a set of strings named dictionary
*/
void setDictionary(std::set<std::string>& dictionary, const std::string& dictionaryPath);