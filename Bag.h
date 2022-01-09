#pragma once
#include <vector>
#include <random>

class Bag {
private:
	vector <char> bag;
public:
	Bag(); //� poss�vel que isto seja obrigat�rio para podermos usar o bag dentro do Game
	Bag(std::vector<char>& bag, mt19937 generator);
	vector<char> getBag();
	char getLastLetter() const;  //meio redundante com a de cima, se n�o for preciso tira-se uma delas (a de cima, acho)
	void addLetter(char letter);
	void removeLetter();
	//setBag � meio redundante com as duas de cima

};

