#include "Bag.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <time.h>

using namespace std;

/**
* @brief construct the bag - define an empty bag as the starting point
*/
Bag::Bag() {
	this->bag = {};
	this->size = 0;
}

//================================================================

int Bag::getSize() const { return this->size; }

//================================================================

/**
* @brief extract and remove the last letter from the bag, changing its size accordingly
* @return char with the extracted letter
*/
char Bag::getLastLetter() {
	char letter = *(this->bag.rbegin());
	this->bag.pop_back();
	this->size--;
	return letter;
}

//================================================================

/**
* @brief shuffle the bag
*/
void Bag::shuffle(mt19937 generator) {
	std::shuffle(this->bag.begin(), this->bag.end(), generator);
}

//================================================================

/**
* @brief adds a new letter to the end of the bag, changing its size accordingly
*/
void Bag::addEndLetter(char letter) {
	this->bag.push_back(letter);
	this->size++;
}

//================================================================

/**
* @brief add a new letter to the bag in a random position, allowing the bag to remain shuffled
*		 change the bag's size accordingly
*/
void Bag::randomlyAddLetter(char letter) {
	this->bag.insert(this->bag.begin() + (rand() % this->bag.size()), letter);
	this->size++;
}