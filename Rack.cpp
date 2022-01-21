#include "Rack.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
* @brief construct a new Rack object: set rack to empty and size to 0
*/
Rack::Rack() {
	this->rack = {};
	this->size = 0;
}

//------------------------------------------------------

/**
* @brief define the rack after a player's turn (possibleRack is created in class Game)
*/
void Rack::setRack(multiset<char> possibleRack) {
	this->rack = possibleRack;
	this->size = possibleRack.size();
}

//------------------------------------------------------

multiset<char> Rack::getRack() const { return this->rack; }

int Rack::getSize() const { return this->size; }

//------------------------------------------------------

/**
* @brief remove the first letter from the rack, changing its size accordingly
* @return char with the removed letter
*/
char Rack::getFirstLetter() {
	char letter = *(this->rack.begin());
	this->rack.erase(rack.begin());
	this->size--;
	return letter;
}

//------------------------------------------------------

/**
* @brief add a new letter to the rack, changing its size accordingly
*/
void Rack::addLetter(char letter) {
	this->rack.insert(letter);
	this->size++;
}

//------------------------------------------------------

/**
* @brief display the rack
*/
void Rack::show(int BOARD_SIZE) const {
	for (int i = 0; i < BOARD_SIZE + 3 - this->rack.size(); i++)
		cout << " ";
	cout << bgGrey << black << " ";
	for (multiset<char>::iterator it = this->rack.begin(); it != rack.end(); it++)
		cout << *it << " ";
	cout << dfltColor << endl << endl;
}