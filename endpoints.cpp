#include "header.hpp"


using namespace std;

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

	rep = handshake(message, CLEMENT_PORT, CLEMENT_ADRESS, AGNES_PORT);
	std::cout << endl << "retour :" << rep;



/*	if (connectTo(clementSocket, CLEMENT_ADRESS, CLEMENT_PORT))
	{
		std::cout << endl << "Agnes envoie " + message + "\n";
		sendTo(clementSocket, message);

		closeSocket(clementSocket);
	}

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
	
	this_thread::sleep_for(chrono::milliseconds(1000));
	if (ListenTo(listenSocket, AGNES_PORT)){
		receiveFrom(listenSocket, message);
		std::cout << endl << "Recu par Agnes : " << message << endl;
		closeSocket(listenSocket);
		cout << endl << "Connection etablie !";
	}
*/



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
	SOCKET agnesSocket = INVALID_SOCKET;
/*
	if (ListenTo(listenSocket, BERNARD_PORT))
	{
		receiveFrom(listenSocket, message);
		std::cout << endl << "Bernard a recu : " << message << endl;
		closeSocket(listenSocket);

		if(connectTo(clementSocket, CLEMENT_ADRESS, CLEMENT_PORT)){
			message = "B et G et P";
			std::cout << endl << "Bernard envoie : " << message << endl;
			sendTo(clementSocket, message);
		}
	}

	if (ListenTo(listenSocket, BERNARD_PORT))
	{
		receiveFrom(listenSocket, message);
		std::cout << endl << "Bernard a recu : " << message << endl;
		closeSocket(listenSocket);

		if(connectTo(agnesSocket, AGNES_ADRESS, AGNES_PORT)){
			message = "B et G et P signés par clément";
			std::cout << endl << "Bernard envoie : " << message << endl;
			sendTo(clementSocket, message);
		}
	}
*/

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
	SOCKET bernardSocket = INVALID_SOCKET;


	rep = rhas(CLEMENT_PORT);

	cout << endl << "recu par rhas" <<  rep;

/*
	if (ListenTo(listenSocket, CLEMENT_PORT)){
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
*/

/*	for (int connectNbr = 0; connectNbr < nbConnection; connectNbr++){


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

		if (ListenTo(listenSocket, CLEMENT_PORT))
		{
			receiveFrom(listenSocket, message);
			std::cout << endl << "Clement a recu :" + message+"\n";

			//CHIFFREMENT ASYMETRIQUE PAR KPRIC
			if (connectTo(bernardSocket, BERNARD_ADRESS, BERNARD_PORT)){
				std::cout << endl << "Clement envoie " + message + "\n";
				sendTo(bernardSocket, "<"+message+">");
				closeSocket(bernardSocket);
			}

			closeSocket(listenSocket);

		}



	}*/


	return 0;
}

string handshake(string message, string portDest, string addrDest, string portSend){

	SOCKET destSocket = INVALID_SOCKET;
	SOCKET sendSocket = INVALID_SOCKET;
	string response;

	if (connectTo(destSocket, addrDest, portDest)){
		std::cout << "handshake 1" << endl;
		sendTo(destSocket, message);
		closeSocket(destSocket);

		if (ListenTo(sendSocket, portSend )){
			receiveFrom(sendSocket, response);
			closeSocket(sendSocket);
		}
	}

	return response;
}

string rhas(string port){

	SOCKET originSocket = INVALID_SOCKET;
	SOCKET listenSocket = INVALID_SOCKET;
	string mes;

	if (ListenTo(listenSocket, port)){
		receiveFrom(listenSocket, mes);
		closeSocket(listenSocket);
	}

	return mes;
}