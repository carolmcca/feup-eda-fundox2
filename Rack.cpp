#include "Rack.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Mariana (?)
/*void setRack(vector<char>& bag, vector<char>& rack, bool restore) {
	if (restore) {
		while (!rack.empty()) {
			char letter = *rack.rbegin();
			rack.pop_back();
			// insert the letter extracted from the rack in a random position of the bag
			bag.insert(bag.begin() + (rand() % bag.size()), letter);
		}
	}

	while (rack.size() < 7 && !bag.empty()) {
		rack.push_back(*bag.rbegin());
		bag.pop_back();
	}
	sort(rack.begin(), rack.end());
}
void show(const vector<char>& rack) {
	cout << endl;
	for (int i = 0; i < BOARD_SIZE + 3 - rack.size(); i++)
		cout << " ";
	cout << bgGrey << black << " ";
	for (int i = 0; i < rack.size(); i++)
		cout << rack[i] << " ";
	cout << dfltColor << endl << endl;
}*/