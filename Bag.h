#pragma once
#include <vector>
#include <random>

class Bag {
private:
	std::vector<char> bag;
	int size;

public:
	Bag();
	Bag(std::vector<char>& bag, std::mt19937 generator);
	char getLastLetter();
	void addLetter(char letter);
	int getSize() const;
};

