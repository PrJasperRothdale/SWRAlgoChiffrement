// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

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

DWORD pid_main, pid_other;


using namespace std;

int Agnes()
{
	std::cout << "AGNES";
	SOCKET clementSocket = INVALID_SOCKET;

	if (connectTo(clementSocket, BERNARD_ADRESS, BERNARD_PORT))
	{
		string message = "test";
		if (sendTo(clementSocket, message))
		{
			std::cout << "Envoyé";
		}
		else
		{
			std::cout << "Erreur";
		}
	}

	return 0;
}

int Bernard()
{
	std::cout << "BERNARD";
	SOCKET listenSocket = INVALID_SOCKET;

	if (ListenTo(listenSocket, BERNARD_PORT))
	{
		string message = "";

		if (receiveFrom(listenSocket, message) > 0)
		{
			std::cout << "nouveau message : "+message;
		}

		closeSocket(listenSocket);
	}

	return 0;
}

int Clement()
{
	std::cout << "CLEMENT";

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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
