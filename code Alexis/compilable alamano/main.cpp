// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstdio>

#include "pch.h"

#define DEFAULT_BUFLEN 1024


#define BERNARD_PORT "27015"
#define BERNARD_ADRESS "127.0.0.1"

#define CLEMENT_PORT "27016"
#define CLEMENT_ADRESS "127.0.0.1"

#define AGNES_PORT "27017"
#define AGNES_ADRESS "127.0.0.1"



int Agnes()
{
	std::string name = "Agnes\n";
	std::cout << name;

	std::string message;
	std::string rep;
	//toutes les clées
	std::string keyAC;
	std::string keyAB;
	std::string keyPriA;
	std::string keyPubB;
	std::string keyPubC;



	SOCKET clementSocket = INVALID_SOCKET;
	message = "test";
	if (connectTo(clementSocket, CLEMENT_ADRESS, CLEMENT_PORT))
	{
		std::cout << "j'envoie " + message + "\n";
		sendTo(clementSocket, message);
	}
	
	/*int t1 = 0;
	int t2 = 0;

	if (keyGenerator(t1, t2))
	{
		std::cout << t1 + " " + t2;
	}*/

	return 0;
}

int Bernard()
{
	std::string name = "Bernard\n";
	std::cout << name;

	std::string message;
	std::string rep;
	//toutes les clées
	std::string keyPriB;
	//string keyPriB;
	std::string keyPubA;
	std::string keyPubC;
	std::string keyAB;
	std::string keyBC;
	
	SOCKET listenSocket = INVALID_SOCKET;

	if (ListenTo(listenSocket, BERNARD_PORT))
	{
		//-----------------------------
		// Do Something
		//-----------------------------

		closeSocket(listenSocket);
	}

	return 0;
}

int Clement(const int nbConnection)
{
	std::string name = "Clément\n";
	std::cout << name;
	std::string message;
	std::string rep;
	//toute les clées
	std::string keyAC;
	std::string keyBC;
	std::string keyPriC;
	std::string keyPubA;

	SOCKET listenSocket = INVALID_SOCKET;
	for (int connectNbr = 0; connectNbr < nbConnection; connectNbr++)
	{
		if (ListenTo(listenSocket, CLEMENT_PORT))
		{
			receiveFrom(listenSocket, message);

			std::cout << "J'ai recu :" + message+"\n";

			closeSocket(listenSocket);
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	if (!InitialiseWinsock())
	{
		return 1;
	}

    std::cout << "Initialisé\n"; 

	if (argc == 1)	// using thread
	{
		std::thread thClement(Clement, 2);
		std::thread thBernard(Bernard);
		// sleep to make sure Clement and bernard are started before Agnes
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::thread thAgnes(Agnes);

		thAgnes.join();
		thBernard.join();
		thClement.join();
	}
	else if (argc == 2) //using three process
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
			Clement(2);
		}
		else
		{
			printf("Invalid argument: %s\n", argv[1]);
			return 1;
		}
	}
	else
	{
		printf("Too many arguments\n");
		return 1;
	}

	CleanupWinsock();

	system("pause");
	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
