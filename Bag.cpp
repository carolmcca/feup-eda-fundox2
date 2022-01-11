#include "Bag.h"
#include <iostream>
#include <vector>
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

Bag::Bag(vector<char>& bag, mt19937 generator) {
	shuffle(bag.begin(), bag.end(), generator);
	this->bag = bag;
	this->size = bag.size();
}

//------------------------------------------------------

char Bag::getLastLetter() {
	char letter = *(this->bag.rbegin());
	this->bag.pop_back();
	this->size--;
	return letter;
}

//------------------------------------------------------

void Bag::addLetter(char letter) {
	this->bag.insert(this->bag.begin() + (rand() % this->bag.size()), letter);
	this->size++;
}


//----------------------------------------------------------

int Bag::getSize() const { 
	return this->size;
}

//----------------------------------------------------------