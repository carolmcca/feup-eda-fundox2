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

void readConfig(int& scoreMax, std::string& dictionaryPath, std::vector<char>& bag);

void readNumPlayers(int& numPlayers);
void readNamePlayer(std::string& name, const int& index);

void setDictionary(std::set<std::string>& dictionary, const std::string& path);