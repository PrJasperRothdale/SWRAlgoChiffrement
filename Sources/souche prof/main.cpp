
#include <thread>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "Util.h"

#define DEFAULT_BUFLEN 1024

#define BERNARD_PORT "27015"
#define BERNARD_ADRESS "127.0.0.1"

#define CLEMENT_PORT "27016"
#define CLEMENT_ADRESS "127.0.0.1"

int Agnes()
{
	SOCKET clementSocket = INVALID_SOCKET;

	if (connectTo(clementSocket, CLEMENT_ADRESS, CLEMENT_PORT))
	{
		//-----------------------------
		// Do Something
		//-----------------------------
	}

	return 0;
}

int Bernard()
{
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
	SOCKET listenSocket = INVALID_SOCKET;
	for (int connectNbr = 0; connectNbr  < nbConnection; connectNbr++)
	{
		if (ListenTo(listenSocket, CLEMENT_PORT))
		{
			//-----------------------------
			// Do Something
			//-----------------------------

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