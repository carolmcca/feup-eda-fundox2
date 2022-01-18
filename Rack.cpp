#include "Rack.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Rack::Rack() {
	this->rack = {};
	this->size = 0;
}


multiset<char> Rack::getRack() const {
	return this->rack;
}

char Rack::getFirstLetter() {
	char letter = *(this->rack.begin());
	this->rack.erase(rack.begin());
	this->size--;
	return letter;
}

void Rack::addLetter(char letter) {
	this->rack.insert(letter);
	this->size++;
}

void Rack::setRack(multiset<char> possibleRack) {
	this->rack = possibleRack;
	this->size = possibleRack.size();
}

int Rack::getSize() const {
	return this->size;
}

void Rack::show(int BOARD_SIZE) const { 
	for (int i = 0; i < BOARD_SIZE + 3 - this->rack.size(); i++)
		cout << " ";
	cout << bgGrey << black << " ";
	for (multiset<char>::iterator it = this->rack.begin(); it != rack.end(); it++)
		cout << *it << " ";
	cout << dfltColor << endl << endl;
}
