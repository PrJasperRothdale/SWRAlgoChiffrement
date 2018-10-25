#include "header.hpp"

using namespace std;

int main(int argc, char **argv)
{
	if (!InitialiseWinsock())
		return 1;

    cout << "Initialisé\n";
	
	if (argc == 1)
	{
		thread thBernard(Bernard);
		thread thClement(Clement);
		// sleep to make sure Clement and bernard are started before Agnes
		this_thread::sleep_for(chrono::milliseconds(1));
		thread thAgnes(Agnes);

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