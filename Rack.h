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
	void show(int BOARD_SIZE) const;
	char getFirstLetter(); //also eliminates the letter from de rack
	int getSize() const;
	void addLetter(char letter);
	void sort();
};
