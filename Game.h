#pragma once
#include "Game.h"
#include "Board.h"
#include "Rack.h"
#include "Turn.h"
#include "Player.h"
#include "Bag.h"

class Game {
public:
	Game(const Bag& bag, const Rack& rack, const Board& board, const Turn& turn, int SCORE_MAX, const string& dictionaryPath);

	void decreaseNumPlayers();
	void setBag(char letter = '0'); //dependendo se está a pôr ou tirar letras, usa uma ou outra das funções da classe Bag

	//se metermos o main todo dentro do game, acho que há aqui uns qts gets que não servem para nada (same para o decreaseNumPlayers)
	//Rack getRack ();
	//Board getBoard();
	//Turn getTurn();
	int getINITIALNUMPLAYERS() const;
	int getNumPlayers() const;
	int getSCOREMAX() const;
	/*void setRack();*/ //o comentário de baixo aplica-se
	/*void setPossibleRack();*/ //depende das funções set da classe Rack
	/*void setTurn();*/ //depende das funções set da classe Turn
	void setWinnerPlayers();
	void showWinners();

	//isto afinal não é aqui, certo?
	//bool isValid();
	/*void getHalfLine(int& index, int*& row, int*& col, std::string& testWord, std::vector<Player**>& changePlayer, bool changeColor, int step);
	std::string getLine(int& index, int*& row, int*& col, const std::string wordPart, std::vector<Player**>& changePlayer, bool changeColor);
	bool checkWordPlacement(const std::string path, Player& player, std::vector<Player**>& changePlayer);*/

	void updateScores();
	void showScores() const;
	void playTheGame();
private:
	Bag bag;
	std::vector<Player> players;
	Rack rack, possibleRack;
	Board board;
	Turn turn;
	int INITIAL_NUM_PLAYERS, numPlayers;
	int SCORE_MAX;
	string dictionaryPath;
	vector<Player**> changePlayer; //vamos mudar isto
	bool isFirstWord;
	int current; //acho que não faz parte do game (?)
	int passTurns, passRounds;
	vector<Player*> winnerPlayers;
	bool restoreRack; //daqui para baixo não sei até que ponto faz sentido estarem aqui
	bool validPosition;
	bool isConnected;
};