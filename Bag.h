#pragma once
#include <vector>
#include <random>

class Bag {
private:
	std::vector<char> bag;
	int size;
public:
	Bag(); //� poss�vel que isto seja obrigat�rio para podermos usar o bag dentro do Game
	Bag(std::vector<char>& bag, std::mt19937 generator);
	//std::vector<char> getBag();
	char getLastLetter();
	void addLetter(char letter);
	void removeLetter();
	int getSize() const;
	//setBag � meio redundante com as duas de cima

};

