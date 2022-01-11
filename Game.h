#pragma once
#include "Game.h"
#include "Board.h"
#include "Rack.h"
#include "Turn.h"
#include "Player.h"
#include "Bag.h"
#include "utils.h"
#include <set>

class Game {
private:
	Bag bag;
	std::vector<Player> players;
	Rack rack;
	Board board;
	std::set<std::string> dictionary;
	int INITIAL_NUM_PLAYERS, numPlayers;
	int SCORE_MAX; // TODO const
	std::vector<int*> changePlayer; //TODO vamos mudar isto
	std::vector<Player*> winnerPlayers;
public:
	Game(const Bag& bag, const Board& board, std::vector<Player>& players, int SCORE_MAX, const std::set<std::string>& dictionary);

	void decreaseNumPlayers();
	//void setBag(char letter = '0'); //dependendo se est� a p�r ou tirar letras, usa uma ou outra das fun��es da classe Bag

	//se metermos o main todo dentro do game, acho que h� aqui uns qts gets que n�o servem para nada (same para o decreaseNumPlayers)
	//Rack getRack ();
	//Board getBoard();
	//Turn getTurn();
	int getINITIALNUMPLAYERS() const;
	int getNumPlayers() const;
	int getSCOREMAX() const;
	void fillRack(bool restoreRack); //o coment�rio de baixo aplica-se
	/*void setPossibleRack();*/ //depende das fun��es set da classe Rack
	/*void setTurn();*/ //depende das fun��es set da classe Turn
	void setWinnerPlayers();
	void showWinners();

	void updateScores();
	void showScores() const;
	void run();

	std::vector<char> checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected);
	bool checkWordPlacement(const Turn& turn, Player& player, std::vector<int*>& changePlayer, bool& isConnected);
	void getHalfLine(const int* boardSize, int& index, int*& row, int*& col, std::string& testWord, std::vector<int*>& changePlayer, bool changeColor, int step);
	std::string getLine(const int* boardSize, int& index, int*& row, int*& col, const std::string wordPart, std::vector<int*>& changePlayer, bool changeColor);



};