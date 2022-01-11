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



class Turn {
private:
	std::string word;
	int row;
	int col;
	bool isVertical;
public:
	Turn();
	std::string getWord() const;
	int getRow() const;
	int getCol() const;
	bool getIsVertical() const;
	char getWordLetter(int i) const;
	TurnPlay readWord(const std::string& message, const std::set<std::string>& dictionary);
	void readDirection();
	void readPosition();
};

