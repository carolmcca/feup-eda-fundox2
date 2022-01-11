#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "utils.h"

using namespace std;

Player::Player(string name, int id) {
	this->name = name;
	this->id = id;
	this->color = colors[id];
	this->score = 0;
	this->gaveUp = false;
}

//----------------------------------------------------

void Player::setName(const string& name) {
	this->name = name;
}

//-----------------------------------------------------

void Player::setColor(const string& color) {
	this->color = color;
}

//------------------------------------------------------

void Player::setScore(const int& score) {
	this->score = score;
}

//------------------------------------------------------

void Player::setGaveUp(const bool& gaveUp) {
	this->gaveUp = gaveUp;
}

//-------------------------------------------------------

string Player::getName() const {
	return this->name;
}

//--------------------------------------------------------

string Player::getColor() const {
	return this->color;
}

//---------------------------------------------------------

int Player::getScore() const {
	return this->score;
}

//---------------------------------------------------------

bool Player::getGaveUp() const {
	return this->gaveUp;
}

//----------------------------------------------------------

void Player::incScore() {
	this->score++;
}

void Player::setId(int id) {
	this->id = id;
}

int Player::getId() const {
	return this->id;
}