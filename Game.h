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
	Bag bag;
	std::vector<Player> players;
	Rack rack;
	Board board;
	std::set<std::string> dictionary;
	int INITIAL_NUM_PLAYERS;
	int numPlayers;
	int SCORE_MAX; // TODO const
	std::vector<int*> changePlayer; //TODO vamos mudar isto
	std::vector<Player*> winnerPlayers;
public:
	Game(std::mt19937 generator);

	void readConfig(std::string& dictionaryPath, std::mt19937 generator);
	void readNumPlayers();
	void readNamePlayers();
	void setDictionary(const std::string& dictionaryPath);

	void fillRack(bool restoreRack);
	void decreaseNumPlayers();
	void updateScores();
	void showScores() const;

	std::vector<char> checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected);
	bool checkWordPlacement(const Turn& turn, Player& player, std::vector<int*>& changePlayer, bool& isConnected);
	void getHalfLine(const int* boardSize, int& index, int*& row, int*& col, std::string& testWord, std::vector<int*>& changePlayer, bool changeColor, int step);
	std::string getLine(const int* boardSize, int& index, int*& row, int*& col, const std::string wordPart, std::vector<int*>& changePlayer, bool changeColor);

	void run();
	void setWinnerPlayers();
	void showWinners();
};