#pragma once
#include <string>
#include <vector>

class Player {
private:
	std::string name;
	std::string color;
	int score;
	bool gaveUp;
	int id;

public:
	Player(std::string name, int id);
	void setName(const std::string& name);
	void setColor(const std::string& color);
	void setScore(const int& score);
	void setGaveUp(const bool& gaveUp);
	std::string getName() const;
	std::string getColor() const;
	int getScore() const;
	bool getGaveUp() const;
	void incScore();
	void setId(int id);
	int getId() const;
};
