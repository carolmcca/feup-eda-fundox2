#include "fundox.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <random>
#include <time.h>

using namespace std;

int main() {
	// initialize a seed and random generator to use algorithm shuffle() on the construction of the object bag
	srand(time(NULL));
	random_device rd;
	mt19937 generator(rd());

	Game game(generator);
	
	game.run();
	game.setWinnerPlayers();
	game.showWinners();

	return 0;
}
