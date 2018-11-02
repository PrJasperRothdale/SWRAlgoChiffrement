#include "header.hpp"

using namespace std;


////////////////////////////endpoints

/////////////////////////////////////





int main(int argc, char **argv)
{
	if (!InitialiseWinsock())
	{
		cout << endl << "Erreur d'initialisation des sockets";
		return 1;
	}
	cout << endl << "Initialisé"; 


	thread thClement(Clement, 2);
	thread thBernard(Bernard);
	// sleep to make sure Clement and bernard are started before Agnes
	this_thread::sleep_for(chrono::milliseconds(1));
	thread thAgnes(Agnes);




	thAgnes.join();
	thBernard.join();
	thClement.join();

	CleanupWinsock();

	system("pause");
	return 0;
}