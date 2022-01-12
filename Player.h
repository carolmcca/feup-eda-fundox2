#pragma once
#include <string>
#include <vector>
#include "utils.h"

class Player {
private:
	std::string name; /// name chosen by the player. If the player doesn't choose any name, it's set to PlayerX
	std::string color; /// player's color (used to show their name and their letters on the board)
	int score; /// player's score
	bool gaveUp; /// indicates whether the player has given up
	int id; /// identifies the player by an int (index on the vector of players -> attribute of class Game)

public:

	/**
	 * @brief Construct a new Player object: set the name and id of the player to the values of the respective parameters
	 */
	Player(std::string name, int id);

	void setGaveUp(const bool& gaveUp);

	std::string getName() const;
	std::string getColor() const;
	int getScore() const;
	bool getGaveUp() const;

	/**
	 * @brief sets the score to 0 
	 */
	void resetScore();

	/**
	 * @brief increases the score by 1
	 */
	void incScore();
};
