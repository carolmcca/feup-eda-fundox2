#pragma once
#include <string>
#include <vector>
#include "utils.h"

class Player {
private:
	std::string name; /// name chosen by the player. If the player doesn't choose any name, it's set to PlayerX, being X the number of the player
	std::string color; /// player's color (used to show their name and letters on the board)
	int score; /// player's score
	int id; /// identification of the player by an int

public:
	Player(int id);

	std::string getName() const;
	std::string getColor() const;
	int getScore() const;
	int getId() const;

	std::string readName();

	void resetScore();
	void incScore();
};
