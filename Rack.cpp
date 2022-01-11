#include "Rack.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Rack::Rack() {
	this->rack = {};
	this->size = 0;
}


vector<char> Rack::getRack() const {  //TODO: multisets
	return this->rack;
}

char Rack::getLastLetter() {
	char letter = *(this->rack.rbegin());
	this->rack.pop_back();
	this->size--;
	return letter;
}

void Rack::addLetter(char letter) {
	this->rack.push_back(letter);
	this->size++;
}

void Rack::setRack(vector<char> possibleRack) {
	this->rack = possibleRack;
	this->size = possibleRack.size();
}

int Rack::getSize() const {
	return this->size;
}

void Rack::show(int BOARD_SIZE) const {   // tenho de procurar sobre multisets
	cout << endl; //TODO: não sei se deixava aqui os endl, ou pelo menos o do inicio acho que punha tipo no show board ou assim
	for (int i = 0; i < BOARD_SIZE + 3 - this->rack.size(); i++)
		cout << " ";
	cout << bgGrey << black << " ";
	for (int i = 0; i < rack.size(); i++)
		cout << rack[i] << " ";
	cout << dfltColor << endl << endl;
}

void Rack::sort() {
	std::sort(this->rack.begin(), this->rack.end());
}
