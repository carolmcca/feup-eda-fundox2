#pragma once
#include "Bag.h"
#include "utils.h"

class Rack {
private:
	std::multiset<char> rack; /// multiset with the letters of the rack
	int size; /// rack's size
	int maxSize; /// rack's full size
public:
	Rack();
	void setRack(std::multiset<char> possibleRack);
	void setMaxSize(int maxSize);

	std::multiset<char> getRack() const;
	int getSize() const;
	char getFirstLetter();
	int getMaxSize() const;

	void addLetter(char letter);
	void show(int BOARD_SIZE) const;
};