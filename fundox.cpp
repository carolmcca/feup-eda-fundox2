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
	// Initialize a seed and random generator to use algorithm shuffle() on the construction of the object Bag
	srand(time(NULL));
	random_device rd;
	mt19937 generator(rd());

	Game game(generator); //TODO: faz sentido deixar o generator a passar aqui? Ou deixo só a seed e o gerador é criado no bag?
	
	game.run();
	game.setWinnerPlayers();
	game.showWinners();

	return 0;
}
