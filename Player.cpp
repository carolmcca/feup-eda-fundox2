#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

/**
* @brief Construct a new Player object: set the name and id of the player to the values of the respective parameters
*/
Player::Player(int id) {
	this->name = ""; //TODO: faz sentido inicializar como PlayerX e depois mudar se o utilizador meter nome?
	this->id = id; //TODO: atribuir id automaticamente? - teriamos que ter um atributo static numPlayers ou assim
	this->color = colors[id];
	this->score = 0;
}

//------------------------------------------------------

string Player::getName() const { return this->name; }

string Player::getColor() const { return this->color; }

int Player::getScore() const { return this->score; }

int Player::getId() const { return this->id; }

//------------------------------------------------------

/**
* @brief Read a string (name) from the keyboard
* 
* @return string with the name chosen by the player
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

/**
* @brief Set the score to 0
*/
void Player::resetScore() { this->score = 0; }

/**
* @brief Increase the atribute score by 1
*/
void Player::incScore() { this->score++; }

//------------------------------------------------------
