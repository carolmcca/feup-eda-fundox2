#pragma once
#include <vector>
#include <random>

class Bag {
private:
	std::vector<char> bag;
	int size;

public:
	Bag();

	int getSize() const;

	void shuffle(std::mt19937 generator);
	char getLastLetter(); //TODO: juntar à getSize()? Não sei até que ponto faz sentido porque não é uma get "normal"
	void randomlyAddLetter(char letter);
	void addEndLetter(char letter);
};

