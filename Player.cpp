#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

Player::Player(int id) {
	this->name = ""; //TODO: faz sentido inicializar como PlayerX e depois mudar se o utilizador meter nome?
	this->id = id;
	this->color = colors[id];
	this->score = 0;
	this->gaveUp = false;
}

//------------------------------------------------------

void Player::setGaveUp(const bool& gaveUp) { this->gaveUp = gaveUp; }

//------------------------------------------------------

string Player::getName() const { return this->name; }

string Player::getColor() const { return this->color; }

int Player::getScore() const { return this->score; }

bool Player::getGaveUp() const { return this->gaveUp; }

//------------------------------------------------------

void Player::resetScore() { this->score = 0; }

void Player::incScore() { this->score++; }

//------------------------------------------------------

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
