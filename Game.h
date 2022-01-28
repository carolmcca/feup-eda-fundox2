#pragma once
#include "Board.h"
#include "Rack.h"
#include "Turn.h"
#include "Player.h"
#include "Bag.h"
#include "utils.h"
#include <set>

class Game {
private:
	Bag bag; /// game bag
	std::vector<Player> players; /// vector with the players
	Rack rack; /// game rack
	Board board; /// game board
	std::set<std::string> dictionary; /// set with the valid words
	int INITIAL_NUM_PLAYERS; /// initial number of players
	int numPlayers; /// current number of players
	int SCORE_MAX; /// score to win the game
	std::vector<int*> changePlayer;  /// vector with pointers to the ids of the board entries stolen by the player 
	std::vector<Player*> winnerPlayers; /// vector with pointers to the winners
	
	void readConfig(std::string& dictionaryPath, std::mt19937 generator);
	void readNumPlayers();
	void readNamePlayers();
	void setDictionary(const std::string& dictionaryPath);

	void fillRack(bool restoreRack);
	void updateScores();
	void showScores() const;
	void updateBoard(const Turn& turn, int playerId);

	std::multiset<char> checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected);
	bool checkWordPlacement(const Turn& turn, Player& player, std::vector<int*>& changePlayer, bool& isConnected);
	void getHalfLine(const int* boardSize, int& index, int*& row, int*& col, std::string& testWord, std::vector<int*>& changePlayer, bool changeColor, int step);
	std::string getLine(const int* boardSize, int& index, int*& row, int*& col, const std::string wordPart, std::vector<int*>& changePlayer, bool changeColor);
public:
	Game(std::mt19937 generator);

	void run();
	void setWinnerPlayers();
	void showWinners();
};