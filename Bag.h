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
	void addRandomLetter(char letter); //TODO: change name
	void addEndLetter(char letter);
	int getSize() const;
	void show();
};

