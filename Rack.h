#pragma once
#include "Bag.h"

class Rack {
private:
	//std::multiset rack;
	vector<char> rack;
public:
	Rack();
	void setRack(const std::vector<char>& rack);
	void setRack(const std::vector<char>& remove, const std::vector<char>& add);
	std::vector<char> getRack() const;
	//std::multiset getRack() const;
	void show() const;

};