#include "Bag.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <time.h>


using namespace std;

Bag::Bag() {
	
}

//-----------------------------------------------------

Bag::Bag(vector<char>& bag, mt19937 generator) {
	shuffle(bag.begin(), bag.end(), generator);
	this->bag = bag;
}
//-----------------------------------------------------

vector <char> Bag::getBag() {
	return this->bag;
}

//------------------------------------------------------

char Bag::getLastLetter() const {
	return *(this->bag.rbegin());
}

//------------------------------------------------------

void Bag::addLetter(char letter) {
	this->bag.insert(this->bag.begin() + (rand() % this->bag.size()), letter);
}


//-------------------------------------------------------

void Bag::removeLetter() {
	this->bag.pop_back();
}
//----------------------------------------------------------