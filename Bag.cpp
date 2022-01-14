#include "Bag.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <time.h>

using namespace std;

Bag::Bag() {
	this->bag = {};
	this->size = 0;
}

//-----------------------------------------------------

void Bag::shuffle(mt19937 generator) {
	std::shuffle(this->bag.begin(), this->bag.end(), generator);
}

//------------------------------------------------------

char Bag::getLastLetter() {
	char letter = *(this->bag.rbegin());
	this->bag.pop_back();
	this->size--;
	return letter;
}

//----------------------------------------------------------

int Bag::getSize() const { return this->size; }

//------------------------------------------------------

void Bag::addRandomLetter(char letter) {
	this->bag.insert(this->bag.begin() + (rand() % this->bag.size()), letter);
	this->size++;
}

//-------------------------------------------------------

void Bag::addEndLetter(char letter) {
	this->bag.push_back(letter);
	this->size++;
}

//-------------------------------------------------------