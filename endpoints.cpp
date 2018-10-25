
#include "header.hpp"

int Agnes()
{
	string name = "Agnes";
	std::cout << name;

	string message;
	string rep;
	//toutes les clées
	string keyAC;
	string keyAB;
	string keyPriA;
	string keyPubB;
	string keyPubC;

	//Envoie de donnée
	std::string port = BERNARD_PORT;
	std::string adress = BERNARD_ADRESS;
	envoieA(adress, port, message);

	rep = recevoir(AGNES_PORT);

	return 0;
}

int Bernard()
{
	string name = "Bernard";
	std::cout << name;

	string message;
	string rep;
	//toutes les clées
	string keyPriB;
	string keyPriB;
	string keyPubA;
	string keyPubC;
	string keyAB;
	string keyBC;
	
	long B;


	return 0;
}

int Clement()
{
	string name = "Clément";
	std::cout << name;
	string message;
	string rep;
	//toute les clées
	string keyAC;
	string keyBC;
	string keyPriC;
	string keyPubA;


	return 0;
}
