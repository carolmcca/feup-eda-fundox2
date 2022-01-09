#pragma once
#include "Game.h"
#include "Board.h"
#include "Rack.h"
#include "Turn.h"
#include "Player.h"
#include "Bag.h"

class Game {
private:
	Bag bag;
	std::vector<Player> players;
	Rack rack, possibleRack;
	Board board;
	Turn turn;
	std::set<std::string> dictionary;
	int INITIAL_NUM_PLAYERS, numPlayers;
	int SCORE_MAX; // TODO const
	string dictionaryPath;
	vector<Player**> changePlayer; //vamos mudar isto
	bool isFirstWord;
	int current; //acho que n�o faz parte do game (?)
	int passTurns, passRounds;
	vector<Player*> winnerPlayers;
	bool restoreRack; //daqui para baixo n�o sei at� que ponto faz sentido estarem aqui
public:
	Game(const Bag& bag, const Board& board, std::vector<Player>& players, int SCORE_MAX, const std::set<std::string>& dictionary);

	void decreaseNumPlayers();
	void setBag(char letter = '0'); //dependendo se est� a p�r ou tirar letras, usa uma ou outra das fun��es da classe Bag

	//se metermos o main todo dentro do game, acho que h� aqui uns qts gets que n�o servem para nada (same para o decreaseNumPlayers)
	//Rack getRack ();
	//Board getBoard();
	//Turn getTurn();
	int getINITIALNUMPLAYERS() const;
	int getNumPlayers() const;
	int getSCOREMAX() const;
	/*void setRack();*/ //o coment�rio de baixo aplica-se
	/*void setPossibleRack();*/ //depende das fun��es set da classe Rack
	/*void setTurn();*/ //depende das fun��es set da classe Turn
	void setWinnerPlayers();
	void showWinners();

	//isto afinal n�o � aqui, certo?
	//bool isValid();
	/*void getHalfLine(int& index, int*& row, int*& col, std::string& testWord, std::vector<Player**>& changePlayer, bool changeColor, int step);
	std::string getLine(int& index, int*& row, int*& col, const std::string wordPart, std::vector<Player**>& changePlayer, bool changeColor);
	bool checkWordPlacement(const std::string path, Player& player, std::vector<Player**>& changePlayer);*/

	void updateScores();
	void showScores() const;
	void run();

	vector<char> checkExistingLetters(Turn& turn, bool& validPosition, bool& isConnected);
	bool checkWordPlacement(const Turn& turn, const string path, Player& player, vector<Player**>& changePlayer, bool& isConnected);
	void getHalfLine(int& index, int*& row, int*& col, string& testWord, vector<Player**>& changePlayer, bool changeColor, int step);
	string getLine(int& index, int*& row, int*& col, const string wordPart, vector<Player**>& changePlayer, bool changeColor);



};