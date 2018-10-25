//------------------------------------------------
// Socket code is copy from microsft documentation
// https://docs.microsoft.com/en-us/windows/desktop/winsock/getting-started-with-winsock
//------------------------------------------------

#include "Util.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

//----------------------------------------
// Fonctions de chiffrement
std::string Encrypt(const std::string& inMessage, const std::string& key)
{
	// TODO
	return inMessage;
}

std::string Decrypt(const std::string& inCryptogram, const std::string& key)
{
	// TODO
	return inCryptogram;
}	

std::string CalculateMAC(const std::string& inMessage, const std::string& secret)
{
	// TODO
	return secret;
}
//----------------------------------------

//----------------------------------------
//Fonctions réseaux
bool InitialiseWinsock()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return false;
	}
	return true;
}

void CleanupWinsock()
{
	WSACleanup();
}

bool ListenTo(SOCKET& clientSocket, const std::string& port)
{
	SOCKET listenSocket = INVALID_SOCKET;

	int iResult;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
	if (iResult != 0) {
		printf("Server : getaddrinfo failed with error: %d\n", iResult);
		return false;
	}

	// Create a SOCKET for connecting to server
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		printf("Server : socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		return false;
	}

	// Setup the TCP listening socket
	iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("Server : bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listenSocket);
		return false;
	}

	freeaddrinfo(result);

	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("Server : listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		return false;
	}

	// Accept a client socket
	clientSocket = accept(listenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		printf("Server : accept failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		return false;
	}

	// No longer need server socket
	closesocket(listenSocket);

	return true;
}

bool connectTo(SOCKET& connectSocket, const std::string& address, const std::string& port)
{
	int iResult;
	struct addrinfo *result;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) 
	{
		printf("Client : getaddrinfo failed with error: %d\n", iResult);
		return false;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype,	ptr->ai_protocol);
		if (connectSocket == INVALID_SOCKET)
		{
			printf("Client : socket failed with error: %ld\n", WSAGetLastError());
			return false;
		}

		// Connect to server.
		iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (connectSocket == INVALID_SOCKET) {
		return false;
	}

	return true;
}

bool closeSocket(SOCKET& socket)
{
	int iResult = 0;
	if (socket != INVALID_SOCKET)
	{
		iResult = closesocket(socket);
		socket = INVALID_SOCKET;
		if (iResult == 0)
		{
			return true;
		}
		else
		{
			printf("Server : closesocket failed with error: %d\n", WSAGetLastError());
			return false;
		}
	}
	return true;
}


bool sendTo(SOCKET& socket, const std::string& inMessage)
{
	int iResult;
	// Send an initial buffer
	iResult = send(socket, inMessage.c_str(), (int)inMessage.size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("Server : send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		return false;
	}
	return true;
}

int receiveFrom(SOCKET& socket, std::string& outMessage)
{
	char recvbuf[128];
	memset(recvbuf, 0, 128);

	int iResult;
	// Receive until the peer closes the connection
	iResult = recv(socket, recvbuf, 128, 0);
	if (iResult > 0)
	{
		outMessage = recvbuf;
	}
	else if (iResult == 0)
	{
		outMessage.clear();
	}
	else
	{
		printf("Server : recv failed with error: %d\n", WSAGetLastError());
		outMessage.clear();
	}

	return iResult;
}

//----------------------------------------