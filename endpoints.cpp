#include "header.hpp"


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
	SOCKET bernardSocket = INVALID_SOCKET;
	SOCKET listenSocket = INVALID_SOCKET;
	message = "test";
	if (connectTo(clementSocket, CLEMENT_ADRESS, CLEMENT_PORT))
	{
		std::cout << endl << "Agnes envoie " + message + "\n";
		sendTo(clementSocket, message);

		closeSocket(clementSocket);
	}

	//this_thread::sleep_for(chrono::milliseconds(1000));
	if (ListenTo(listenSocket, AGNES_PORT)){
		receiveFrom(listenSocket, message);
		std::cout << endl << "Recu par Agnes : " << message << endl;
		closeSocket(listenSocket);
	}

	if (connectTo(bernardSocket, BERNARD_ADRESS, BERNARD_PORT)){
		message = "A et G et P signés";
		std::cout << "Agnes envoie " + message + "\n";
		sendTo(bernardSocket, message);
		closeSocket(bernardSocket);
	}
	


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
	SOCKET clementSocket = INVALID_SOCKET;

	if (ListenTo(listenSocket, BERNARD_PORT))
	{
		receiveFrom(listenSocket, message);
		std::cout << endl << "Bernard a recu : " << message << endl;
		closeSocket(listenSocket);

		if(connectTo(clementSocket, CLEMENT_ADRESS, CLEMENT_PORT)){
			message = "B et G et P signes par clement";
			std::cout << endl << "Bernard envoie : " << message << endl;
			sendTo(clementSocket, message);
		}
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
	SOCKET agnesSocket = INVALID_SOCKET;
	//for (int connectNbr = 0; connectNbr < nbConnection; connectNbr++)
	while (1)
	{
		if (ListenTo(listenSocket, CLEMENT_PORT))
		{
			receiveFrom(listenSocket, message);
			std::cout << endl << "Clement a recu :" + message+"\n";

			//CHIFFREMENT ASYMETRIQUE PAR KPRIC
			if (connectTo(agnesSocket, AGNES_ADRESS, AGNES_PORT)){
				std::cout << endl << "Clement envoie " + message + "\n";
				sendTo(agnesSocket, "<"+message+">");
				closeSocket(agnesSocket);
			}

			closeSocket(listenSocket);

		}



	}


	return 0;
}

