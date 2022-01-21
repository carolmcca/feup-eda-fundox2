#pragma once
#include "utils.h"
#include <string>
#include <set>

/**
 * @brief reveals the player's choice on a given turn
 */
typedef enum {
	PASS,
	GIVEUP,
	PLAY
} TurnPlay;


/**
 * @brief saves the chosen word, position and direction on each turn
 */
class Turn {
private:
	std::string word;
	int row;
	int col;
	bool isVertical;
public:
	Turn();
	TurnPlay readWord(const std::string& message, const std::set<std::string>& dictionary);
	void readPosition(const int BOARD_ROWS, const int BOARD_COLS);
	void readDirection();

	std::string getWord() const;
	int getRow() const;
	int getCol() const;
	bool getIsVertical() const;
	char getWordLetter(int i) const;
};