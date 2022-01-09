#include "Bag.h"
#include <random>
#include <time.h>

using namespace std;

//esta função é extra, não faz parte do bag pq temos de ficar com alguns dos valores e não faz
//sentido serem objetos do bag; TEM DE SER CHAMADA ANTES DE O BAG SER CRIADO!!!

//no main
ifstream extractFile("CONFIG.txt");

if (!extractFile.is_open()) {
	cout << "File CONFIG.txt not found!" << endl;
	exit(1);
}

//função, chamada depois da coisa acima e antes de o bag ser criado
void readConfig(ifstream & extractFile, int& scoreMax, string & dictionaryPath) {

	extractFile.ignore(1000, ':');
	extractFile >> scoreMax;
	extractFile.ignore(1000, ':');
	extractFile >> dictionaryPath;
	extractFile.ignore(1000, ':');
}

//para a declaração ir para dentro da função (em vez de estar no main) podemos pô-la a retornar a ifstream e fica:

//ifstream readConfig(int& scoreMax, string& dictionaryPath) {
//	ifstream extractFile("CONFIG.txt");
//
//	if (!extractFile.is_open()) {
//		cout << "File CONFIG.txt not found!" << endl;
//		exit(1);
//	}
//
//	extractFile.ignore(1000, ':');
//	extractFile >> scoreMax;
//	extractFile.ignore(1000, ':');
//	extractFile >> dictionaryPath;
//	extractFile.ignore(1000, ':');
//
//	return extractFile;
//}

// acho que a versão comentada faz + sentido mas vejam o que acham

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

Bag::Bag()
{
	bag = {};
}

//-----------------------------------------------------

Bag::Bag(ifstream & extractFile)
{
	char letter;
	int num_occurences;

	while (extractFile >> letter >> num_occurences)
		for (int i = 1; i <= num_occurences; i++)
			bag.push_back(letter);

	extractFile.close();

	srand(time(NULL));
	random_device rd;
	mt19937 g(rd());

	shuffle(bag.begin(), bag.end(), g);
}
//-----------------------------------------------------

vector <char> Bag::getBag()
{
	return bag;
}

//------------------------------------------------------

char Bag::getLastLetter() const
{
	return *bag.rbegin();
}

//------------------------------------------------------

void Bag::addLetter(char letter)
{
	bag.insert(bag.begin() + (rand() % bag.size()), letter);
}


//-------------------------------------------------------

void Bag::removeLetter()
{
	bag.pop_back();
}
//----------------------------------------------------------