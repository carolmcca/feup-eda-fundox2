#pragma once
#include <vector>
#include <random>

class Bag {
private:
	std::vector<char> bag; /// game bag: a vector with the letters still available to play
	int size; /// bag's size

public:
	Bag();

	int getSize() const;
	char getLastLetter();

	void shuffle(std::mt19937 generator);
	void addEndLetter(char letter);
	void randomlyAddLetter(char letter);
};