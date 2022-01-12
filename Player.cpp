#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

Player::Player(string name, int id) {
	this->name = name;
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
