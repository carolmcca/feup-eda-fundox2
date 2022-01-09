#include "iostream"
#include "Game.h"
#include "Turn.h"

#include "fundox.h"
#include <iomanip>
#include <algorithm>
#include "utils.h"



using namespace std;
//Turn: faz sentido passar j�? ainda n�o existe
Game::Game(const Bag& bag, const Board& board, vector<Player>& players, int SCORE_MAX, const set<string>& dictionary) {
	this->bag = bag;
	this->board = board;
	this->SCORE_MAX = SCORE_MAX;
	//isto pode n�o ser preciso dependendo do turn | perguntar � Bolinha
	this->dictionary = dictionary;
	this->players = players;

	numPlayers = INITIAL_NUM_PLAYERS;
	isFirstWord = true;
	current = numPlayers - 1;
	passTurns = 0;
	passRounds = 0;
	restoreRack = false;
}
//-------------------------------------------------------------

void Game::decreaseNumPlayers() {
	this->numPlayers--;
}
//-------------------------------------------------------------

void Game::setBag(char letter = '0') {
	if (letter == '0')
		this->bag.removeLetter();
	else
		this->bag.addLetter(letter);
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

void Game::updateScores() {
	for (int i = 0; i < players.size(); i++)
		players[i].setScore(0);

	for (int i = 0; i < board.getSize(); i++) {
		for (int j = 0; j < board.getSize(); j++) {
			if (board.getBoard()[i][j].second != nullptr)
				board.getBoard()[i][j].second->incScore();
		}
	}
}

//-------------------------------------------------------------

void Game::showScores() const {
	cout << endl << setw(board.getSize() - 2) << " ";
	cout << "SCORE BOARD" << endl;

	int gaveUpSize = std::count_if(players.begin(), players.end(), [](const Player& p) { return p.getGaveUp(); });
	cout << setw(board.getSize() - players.size() + gaveUpSize + 1) << " ";
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].getGaveUp())
			cout << players[i].getColor() << setw(3) << players[i].getScore();
	}
	cout << dfltColor << endl;
}

//-------------------------------------------------------------

void Game::run() {
	while (players[current].getScore() < SCORE_MAX && passRounds < 3 && numPlayers > 1) {
		current = (current + 1) % INITIAL_NUM_PLAYERS;

		if (!players[current].getGaveUp())
			continue;
		
		bool restoreRack = (passRounds > 0 && passTurns == 0);
		//setRack(bag, rack, restoreRack);
		showScores();
		board.show();
		//rack.setRack();
		Turn turn;
		
		string message = players[current].getColor()+players[current].getName()+"'s turn"+dfltColor;
		TurnPlay input = turn.readWord(message, dictionaryPath);
		switch (input) {
		case PASS:
			passRounds += (passTurns + 1) / numPlayers;
			passTurns = (passTurns + 1) % numPlayers;
			continue;
		case GIVEUP:
			decreaseNumPlayers();
			passRounds += passTurns / numPlayers;
			players[current].setGaveUp(true);
			continue;
		case PLAY:
			passTurns = 0;
			passRounds = 0;
		}
		//turn.getRow();
		//turn.getCol();
		//turn.getIsVertival();

		bool validPosition = true;
		bool isConnected = isFirstWord;
		vector<char> possibleRack = checkExistingLetters(turn, validPosition, isConnected);
		if (validPosition && checkWordPlacement(turn, dictionaryPath, players[current], changePlayer, isConnected) && isConnected) {
			isFirstWord = false;
			rack.setRack(possibleRack);
			for (int i = 0; i < turn.getWord().length(); i++) {
				// n�o sei se tenho de mudar isto mas n�o me parece
				pair<char, Player*> entry = pair<char, Player*>(toupper(turn.getWordLetter(i)), &players[current]);
				if (turn.getIsVertical())
						board.setEntry(turn.getRow() + i, turn.getCol(), entry);
				else
						board.setEntry(turn.getRow(), turn.getCol() + i, entry);
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
//-------------------------------------------------------------
void Game::setWinnerPlayers()
{
	int numWinners = 0;
	int maxScore = -1;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].getGaveUp()) {
			if (players[i].getScore() > maxScore) {
				winnerPlayers.clear();
				winnerPlayers.push_back(&players[i]);
				maxScore = players[i].getScore();
			}
			else if (players[i].getScore() == maxScore) {
				winnerPlayers.push_back(&players[i]);
			}
		}
	}
}

//-------------------------------------------------------------

void Game::showWinners()
{
	if (winnerPlayers.size() == 1) {
		cout << endl << "   " << bgGrey << winnerPlayers[0]->getColor() << "   " << winnerPlayers[0]->getName() << " WON!   " << dfltColor << endl;
	}
	else if (winnerPlayers.size() > 1) {
		cout << endl << "   " << "It's a tie! Winning players: " << endl;
		for (int i = 0; i < winnerPlayers.size(); i++) {
			cout << "   " << bgGrey << winnerPlayers[i]->getColor() << "   " << winnerPlayers[i]->getName() << "   " << dfltColor << endl;
		}
	}
}

vector<char> Game::checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected) {
	vector<char> r = rack.getRack();

	bool spaceExists = false; // dictates whether or not the word is new 
	int row = turn.getRow();
	int col = turn.getCol();

	turn.wordToUpper();

	for (int i = 0; i < turn.getWord().size(); i++) {
		// the cicle is broken if the word get's out of the board, overlaps with another word or there aren't enough letters to write it
		if (turn.getRow() == this->board.getSize() || turn.getCol() == this->board.getSize()) {
			// the word get's out of the board limits
			cout << "Your word doesn't fit on the board. You lost your turn.\n";
			validPosition = false;
			break;
		}

		if (turn.getWordLetter(i) != board.getEntry(row, col).first) {
			// the char to be inserted is different from the one in the board
			if (board.getEntry(row, col).first == ' ') {
				// the position is free to receive the char
				vector<char>::iterator pos = find(r.begin(), r.end(), turn.getWordLetter(i));
				if (pos != r.end()) {
					// the char to be inserted is on the rack
					spaceExists = true;
					r.erase(pos);
				}
				else {
					// the char isn't on the rack - invalid choice of word
					cout << "You don't have enough letters to write your word. You lost your turn.\n";
					validPosition = false;
					break;
				}
			}
			else {
				// the board already as another char on the position being tested - invalid placement of word
				cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
				validPosition = false;
				break;
			}
		}
		else {
			// the board already has the char being inserted - the word isn't isolated
			isConnected = true;
		}
		if (turn.getIsVertical())
			row++;
		else
			col++;
	}
	validPosition = (validPosition && spaceExists);
	return r;
}

bool Game::checkWordPlacement(const Turn& turn, const string path, Player& player, vector<Player**>& changePlayer, bool& isConnected) {
	changePlayer.clear();
	string testWord;
	bool changeColor;
	int perpendicularIndex, paralelIndex;
	int initialParalelIndex, initialPerpendicularIndex;
	int* row;
	int* col;

	// initialize Indexes -> col is considered parallel to vertical and perpendicular to horizontal
	//                    -> row is considered perpendicular to vertical and parallel to horizontal
	if (turn.getIsVertical()) {
		initialPerpendicularIndex = turn.getRow();
		initialParalelIndex = turn.getCol();
		row = &perpendicularIndex;
		col = &paralelIndex;
	}
	else {
		initialParalelIndex = turn.getRow();
		initialPerpendicularIndex = turn.getCol();
		row = &paralelIndex;
		col = &perpendicularIndex;
	}


	paralelIndex = initialParalelIndex;
	perpendicularIndex = initialPerpendicularIndex;
	// get the word formed in the same direction as the played word
	testWord = getLine(perpendicularIndex, row, col, turn.getWord(), changePlayer, true);
	if (!searchWord(this->dictionary, testWord)) {
		cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
		return false;
	}
	if (testWord.length() > turn.getWord().length())
		isConnected = true;

	for (int i = 0; i < turn.getWord().length(); i++) {
		perpendicularIndex = initialPerpendicularIndex + i;
		paralelIndex = initialParalelIndex;
		changeColor = board.getEntry(*row, *col).first == ' ';

		string letter = { turn.getWordLetter(i) };
		// get the word formed by the letter i of the played word in its perpendicular direction
		testWord = getLine(paralelIndex, row, col, letter, changePlayer, changeColor);
		if (testWord.length() > 1) {
			if (!searchWord(this->dictionary, testWord)) {
				cout << "Your choice of word placement is impossible with the current board. You lost you turn.";
				return false;
			}
			isConnected = true;
		}
	}
	if (!isConnected)
		cout << "You inserted an isolated word. You lost your turn.\n";
	return true;
}

void Game::getHalfLine(int& index, int*& row, int*& col, string& testWord, vector<Player**>& changePlayer, bool changeColor, int step) {
	while (index >= 0 && index < this->board.getSize() && board.getEntry(*row, *col).first != ' ') {
		testWord.push_back(board.getEntry(*row, *col).first);
		if (changeColor)
			changePlayer.push_back(&(board.getEntry(*row, *col).second));
		index += step;
	}
}
string Game::getLine(int& index, int*& row, int*& col, const string wordPart, vector<Player**>& changePlayer, bool changeColor) {
	string testWord;
	index--;
	getHalfLine(index, row, col, testWord, changePlayer, changeColor, -1);
	if (testWord.length() != 0)
		reverse(testWord.begin(), testWord.end());

	testWord += wordPart;

	index += testWord.length() + 1;
	getHalfLine(index, row, col, testWord, changePlayer, changeColor, 1);
	return testWord;
}

//como ficaria o main neste caso (excluindo algumas declara��es de vari�veis das diferentes classes)

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
//	//os players s�o definidos dentro do Game
//	Game game(bag, rack, board, turn, SCORE_MAX, dictionaryPath);
//	game.playTheGame();
//	game.setWinnerPlayers();
//	game.showWinners();
//
//	return 0;
//}