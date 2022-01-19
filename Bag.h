#pragma once
#include <vector>
#include <random>

class Bag {
private:
	std::vector<char> bag;
	int size;

public:
	Bag();
	void shuffle(std::mt19937 generator);
	char getLastLetter();
	void randomlyAddLetter(char letter);
	void addEndLetter(char letter);
	int getSize() const;
};

