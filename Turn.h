#pragma once

/**
 * @brief reveals the player's choice on a given turn
 */
typedef enum {
	PASS,
	GIVEUP,
	PLAY
} TurnPlay;



class Turn {
private:
	std::string word;
	int row;
	int col;
	bool isVertical, validPosition, wordIsConnected;
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
	char getWordLetter(int i) const;
	TurnPlay readWord(const std::string& message, const std::string& dictionary);
	void readDirection();
	void readPosition();
	void wordToUpper();
};