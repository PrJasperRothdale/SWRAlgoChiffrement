// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <vector> 
#include <time.h>   
#include <windows.h>


#include <string>

//Fonctions réseaux
bool InitialiseWinsock();
void CleanupWinsock();

bool ListenTo(SOCKET& socket, const std::string& port);
bool connectTo(SOCKET& socket, const std::string& address, const std::string& port);
bool closeSocket(SOCKET& socket);

bool sendTo(SOCKET& socket, const std::string& inMessage);
int receiveFrom(SOCKET& socket, std::string& outMessage);


bool keyGenerator(std::string& priKey, std::string& pubKey);

int gcd(int a, int b);
#endif //PCH_H
