
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#include <string>

//----------------------------------------
// Fonctions de chiffrement
std::string Encrypt(const std::string& inMessage, const std::string& key);
std::string Decrypt(const std::string& inCryptogram, const std::string& key);

std::string CalculateMAC(const std::string& inMessage, const std::string& secret);
//----------------------------------------

//----------------------------------------
//Fonctions réseaux
bool InitialiseWinsock();
void CleanupWinsock();

bool ListenTo(SOCKET& socket, const std::string& port);
bool connectTo(SOCKET& socket, const std::string& address, const std::string& port);
bool closeSocket(SOCKET& socket);

bool sendTo(SOCKET& socket, const std::string& inMessage);
int receiveFrom(SOCKET& socket, std::string& outMessage);
//----------------------------------------

