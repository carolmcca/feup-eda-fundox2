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
	std::string word; /// word played
	int row; /// word's first letter's row
	int col; /// word's first letter's col
	bool isVertical; /// indicates if the word is played in the vertical (true) or horizontal (false) direction
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