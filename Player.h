#pragma once
#include <string>
#include <vector>
#include "utils.h"

class Player {
private:
	std::string name;
	std::string color;
	int score;
	bool gaveUp;
	int id;

public:
	Player(std::string name, int id);
	void resetScore();
	void setGaveUp(const bool& gaveUp);
	std::string getName() const;
	std::string getColor() const;
	int getScore() const;
	bool getGaveUp() const;
	void incScore();
};
