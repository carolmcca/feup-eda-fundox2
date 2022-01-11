#pragma once
#include "Bag.h"
#include "utils.h"

class Rack {
private:
	//TODO: std::multiset rack;
	std::vector<char> rack;
	int size;
public:
	Rack();
	void setRack(std::vector<char> possibleRack);
	std::vector<char> getRack() const;
	//std::multiset getRack() const;
	void show(int BOARD_SIZE) const;
	char getLastLetter(); //also eliminates the letter from de rack
	int getSize() const;
	void addLetter(char letter);
	void sort();
};
