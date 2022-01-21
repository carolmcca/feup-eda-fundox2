#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

/**
* @brief construct a new Player object - set the name to "", the score to 0, the id to the value of the input parameter and the color corresponding to it
*/
Player::Player(int id) {
	this->name = "";
	this->id = id;
	this->color = colors[id];
	this->score = 0;
}

//========================================================

string Player::getName() const { return this->name; }

string Player::getColor() const { return this->color; }

int Player::getScore() const { return this->score; }

int Player::getId() const { return this->id; }

//========================================================

/**
* @brief read the player's name from the keyboard
* @return string with the name chosen by the player (or default name)
*/
string Player::readName() {
	while (true) {
		cout << colors[this->id] << "Player " << this->id + 1 << ": ";
		getline(cin, this->name);
		cout << dfltColor;
		if (isInputValid("getline", "Please insert a valid name\n")) {
			if (this->name.size() == 0) {
				cout << "Your name will be Player" << this->id + 1 << endl;
				name = "Player" + to_string(this->id + 1);
			}
			return name;
		}
	}
}

//========================================================

/**
* @brief set the score to 0
*/
void Player::resetScore() { this->score = 0; }

//========================================================

/**
* @brief increase the score by 1
*/
void Player::incScore() { this->score++; }