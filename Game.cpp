#include "iostream"
#include "Game.h"
#include "fundox.h"

using namespace std;
//Turn: faz sentido passar já? ainda não existe
Game::Game(const Bag& bag, const Rack& rack, const Board& board, const Turn& turn, int SCORE_MAX, const string& dictionaryPath)
{
	this->bag = bag;
	this->rack = rack;
	/*possibleRack.setRack({});*/
	this->board = board;
	this->turn = turn;
	this->SCORE_MAX = SCORE_MAX;

	//isto pode não ser preciso dependendo do turn | perguntar à Bolinha
	this->dictionaryPath = dictionaryPath;

	while (true) {
		cout << "Please insert the number of players (2-4): ";
		cin >> INITIAL_NUM_PLAYERS;
		//falta o valid
		if (valid("cin") && numPlayers >= 2 && numPlayers <= 4)
			return;
		cout << "The number must be an integer between 2 and 4!" << endl;
	}

	players.resize(INITIAL_NUM_PLAYERS);

	for (int i = 0; i < INITIAL_NUM_PLAYERS; i++) {
		while (true) {
			cout << colors[i] << "Player " << i + 1 << ": ";
			getline(cin, players[i].name);
			cout << dfltColor;
			if (valid("getline", "Please insert a valid name\n")) {
				if (players[i].name.size() == 0) {
					cout << "Your name will be Player" << i + 1 << endl;
					players[i].name = "Player" + to_string(i + 1);
				}
				break;
			}
		}
		players[i].color = colors[i];
		players[i].score = 0;
		players[i].gaveUp = false;
	}

	numPlayers = INITIAL_NUM_PLAYERS;
	changePlayer = {};
	isFirstWord = true;
	current = numPlayers - 1;
	passTurns = 0;
	passRounds = 0;
	winnerPlayers = {};
	restoreRack = false;
	validePosition = true;
	isConnected = true;
}
//-------------------------------------------------------------

void Game::decreaseNumPlayers()
{
	numPlayers--;
}
//-------------------------------------------------------------


void Game::setBag(char letter = '0')
{
	if (letter == '0')
		bag.removeLetter();

	else
		bag.addLetter(letter);
}
//-------------------------------------------------------------

int Game::getINITIALNUMPLAYERS() const
{
	return INITIAL_NUM_PLAYERS;
}
//-------------------------------------------------------------

int Game::getNumPlayers() const
{
	return numPlayers;
}
//-------------------------------------------------------------
int Game::getSCOREMAX() const
{
	return SCORE_MAX;
}
//-------------------------------------------------------------

void Game::updateScores()
{
	for (int i = 0; i < players.size(); i++)
		players[i].score = 0;

	for (int i = 0; i < board.boardSize; i++) {
		for (int j = 0; j < board.boardSize; j++) {
			if (board.boardSize[i][j].second != nullptr)
				board.boardSize[i][j].second->score++;
		}
	}
}
//-------------------------------------------------------------
void Game::showScores() const
{
	cout << endl << setw(board.boardSize - 2) << " ";
	cout << "SCORE BOARD" << endl;
	// não sei como funciona a tradução da linha abaixo
	int gaveUpSize = std::count_if(players.begin(), players.end(), [](const Player& p) { return p.gaveUp; });
	cout << setw(board.boardSize - players.size() + gaveUpSize + 1) << " ";
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].gaveUp)
			cout << players[i].color << setw(3) << players[i].score;
	}
	cout << dfltColor << endl;
}
//-------------------------------------------------------------
void Game::playTheGame()
{
	while (players[current].score < SCORE_MAX && passRounds < 3 && numPlayers > 1) {
		current = (current + 1) % INITIAL_NUM_PLAYERS;

		if (!players[current].gaveUp) {
			bool restoreRack = (passRounds > 0 && passTurns == 0);
			//setRack(bag, rack, restoreRack);
			showScores();
			board.show();
			//rack.setRack();

			//o turn vai ter provavelmente um setWord ou assim que vai entrar aqui
			TurnPlay input = readWord(turn.word, players[current], dictionaryPath);
			switch (input) {
			case PASS:
				passRounds += (passTurns + 1) / numPlayers;
				passTurns = (passTurns + 1) % numPlayers;
				continue;
			case GIVEUP:
				decreaseNumPlayers();
				passRounds += passTurns / numPlayers;
				players[current].gaveUp = true;
				continue;
			case PLAY:
				passTurns = 0;
				passRounds = 0;
			}
			//turn.getRow();
			//turn.getCol();
			//turn.getIsVertival();

			validPosition = true;
			isConnected = isFirstWord;
			possibleRack = checkExistingLetters(board, turn, rack, validPosition, isConnected);
			if (validPosition && checkWordPlacement(board, turn, dictionaryPath, players[current], changePlayer, isConnected) && isConnected) {
				isFirstWord = false;
				rack = possibleRack;
				for (int i = 0; i < turn.word.length(); i++) {
					// não sei se tenho de mudar isto mas não me parece
					pair<char, Player*> entry = pair<char, Player*>(toupper(turn.word[i]), &players[current]);
					if (turn.isVertical)
						//board.getBoard()[turn.row + i][turn.col] = entry;
					else
						//board.getBoard()[turn.row][turn.col + i] = entry;
				}
				for (int i = 0; i < changePlayer.size(); i++)
					*changePlayer[i] = &players[current];

				updateScores();
			}
			else {
				passTurns++;
			}
		}
	}
}
//-------------------------------------------------------------
void Game::setWinnerPlayers()
{
	int numWinners = 0;
	int maxScore = -1;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].gaveUp) {
			if (players[i].score > maxScore) {
				winnerPlayers.clear();
				winnerPlayers.push_back(&players[i]);
				maxScore = players[i].score;
			}
			else if (players[i].score == maxScore) {
				winnerPlayers.push_back(&players[i]);
			}
		}
	}
}

//-------------------------------------------------------------

void Game::showWinners()
{
	if (winnerPlayers.size() == 1) {
		cout << endl << "   " << bgGrey << winnerPlayers[0]->color << "   " << winnerPlayers[0]->name << " WON!   " << dfltColor << endl;
	}
	else if (winnerPlayers.size() > 1) {
		cout << endl << "   " << "It's a tie! Winning players: " << endl;
		for (int i = 0; i < winnerPlayers.size(); i++) {
			cout << "   " << bgGrey << winnerPlayers[i]->color << "   " << winnerPlayers[i]->name << "   " << dfltColor << endl;
		}
	}
}

//como ficaria o main neste caso (excluindo algumas declarações de variáveis das diferentes classes)

//int main()
//{
//	int SCORE_MAX;
//	string dictionaryPath;
//
//	Board(BOARD_SIZE); //magic numbers...?
//
//	ifstream extractFile = readConfig(SCORE_MAX, dictionaryPath);
//
//	Bag bag(extractFile);
//	//Rack rack();
//	//Turn turn();
//
//	//os players são definidos dentro do Game
//	Game game(bag, rack, board, turn, SCORE_MAX, dictionaryPath);
//	game.playTheGame();
//	game.setWinnerPlayers();
//	game.showWinners();
//
//	return 0;
//}