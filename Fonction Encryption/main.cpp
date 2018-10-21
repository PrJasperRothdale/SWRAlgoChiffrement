#include "h.hpp"

using namespace std;



int main(int argc, char *argv[])
{

	if (argc >= 2){
		cout << "Le message est :" << argv[1] << endl;
	}

	string msg (argv[1]);
	string k ("12341234");

	Encrypt(msg,k);

	return 0;
}