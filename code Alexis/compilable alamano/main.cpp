
#include "pch.h"
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstdio>

#define DEFAULT_BUFLEN 1024


#define BERNARD_PORT "27015"
#define BERNARD_ADRESS "127.0.0.1"

#define CLEMENT_PORT "27016"
#define CLEMENT_ADRESS "127.0.0.1"

#define AGNES_PORT "27017"
#define AGNES_ADRESS "127.0.0.1"


using namespace std;

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

int main(int argc, char **argv)
{
	if (!InitialiseWinsock())
	{
		return 1;
	}

    std::cout << "Initialisé\n"; 
	
	if (argc == 1)
	{
		std::thread thBernard(Bernard);
		std::thread thClement(Clement);
		// sleep to make sure Clement and bernard are started before Agnes
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::thread thAgnes(Agnes);

		thAgnes.join();
		thBernard.join();
		thClement.join();
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-a") == 0)
		{
			Agnes();
		}
		else if (strcmp(argv[1], "-b") == 0)
		{
			Bernard();
		}
		else if (strcmp(argv[1], "-c") == 0)
		{
			Clement();
		}
		else
		{
			printf("Invalid argument: %s\n", argv[1]);
			return 1;
		}
	}
	


	CleanupWinsock();
	return 0;
}
