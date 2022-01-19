#include "Bag.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <time.h>

using namespace std;

/**
* @brief constructs the bag - defines an empty bag as the starting point
*/
Bag::Bag() {
	this->bag = {};
	this->size = 0;
}

//-----------------------------------------------------

/**
* @brief shuffles the bag
*/
void Bag::shuffle(mt19937 generator) {
	std::shuffle(this->bag.begin(), this->bag.end(), generator);
}

//------------------------------------------------------

/**
* @brief extracts the bag's last letter - removes the extracted letter from the bag
*				changes the bag's size accordingly
* @return extracted letter
*/
char Bag::getLastLetter() {
	char letter = *(this->bag.rbegin());
	this->bag.pop_back();
	this->size--;
	return letter;
}

//----------------------------------------------------------

/**
* @brief gets the bag's size
* @return bag's size
*/
int Bag::getSize() const { return this->size; }

//------------------------------------------------------

/**
* @brief adds a new letter to the bag - the letter is inserted in a random position, allowing the bag to remain shuffled
*				changes the bag's size accordingly
*/
void Bag::randomlyAddLetter(char letter) {
	this->bag.insert(this->bag.begin() + (rand() % this->bag.size()), letter);
	this->size++;
}

//-------------------------------------------------------

/**
* @brief expands the bag - adds a new letter to the end of the bag
*				changes the bag's size accordingly
*/
void Bag::addEndLetter(char letter) {
	this->bag.push_back(letter);
	this->size++;
}

//-------------------------------------------------------