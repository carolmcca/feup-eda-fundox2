#pragma once
#include <vector>
#include <string>
#include <set>

const std::string dfltColor;
const std::string bgGrey;
const std::string red;
const std::string blue;
const std::string green;
const std::string magenta;
const std::string black;
const std::vector<std::string> colors;

class Rack {
public:
	Rack();
	void setRack(const std::vector<char>& remove, const std::vector<char>& add);
	std::multiset getRack() const;
	void show() const;
private:
	std::multiset rack;
};

class Bag {
public:
	Bag();
	void setBag(const std::vector<char>& remove, const std::vector<char>& add = {});
	std::vector<char> getBag() const;
private:
	std::vector<char> bag;
};

class Game {
public:
	void readConfig();
	bool isValid();
	void getHalfLine(int& index, int*& row, int*& col, std::string& testWord, std::vector<Player**>& changePlayer, bool changeColor, int step);
	std::string getLine(int& index, int*& row, int*& col, const std::string wordPart, std::vector<Player**>& changePlayer, bool changeColor);
	bool checkWordPlacement(const std::string path, Player& player, std::vector<Player**>& changePlayer);
	void updateScores();
	void showScores() const;
private:
	Bag bag;
	std::vector<Player> players;
	Rack rack;
	Board board;
	Turn turn;
};

class Turn {
public:
	Turn();
	void setWord(const std::string& word);
	void setRow(const int& row); //passar por ref?
	void setCol(const int& col);
	void setIsVertical(const bool& isVertical);
	std::string getWord() const;
	int getRow() const;
	int getCol() const;
	bool getIsVertical() const;
	//...
	std::vector<char> checkExistingLetters(const std::vector<char>& boardLine, std::vector<char> rack);
private:
	std::string word;
	int row;
	int col;
	bool isVertical, validPosition, wordIsConnected;
};
