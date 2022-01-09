#pragma once
#include <string>
#include <vector>
#include <fstream>

class Bag {
public:
	Bag(); //é possível que isto seja obrigatório para podermos usar o bag dentro do Game
	Bag(ifstream& extractFile);
	vector <char> getBag();
	char getLastLetter() const;  //meio redundante com a de cima, se não for preciso tira-se uma delas (a de cima, acho)
	void addLetter(char letter);
	void removeLetter();
	//setBag é meio redundante com as duas de cima
private:
	vector <char> bag;
};

