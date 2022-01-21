#pragma once
#include "Bag.h"
#include "utils.h"

class Rack {
private:
	std::multiset<char> rack;
	int size;
public:
	Rack();
	void setRack(std::multiset<char> possibleRack);

	std::multiset<char> getRack() const;
	int getSize() const;
	char getFirstLetter();

	void addLetter(char letter);
	void show(int BOARD_SIZE) const;
};