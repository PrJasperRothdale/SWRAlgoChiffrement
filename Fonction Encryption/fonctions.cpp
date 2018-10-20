#include "h.hpp"

using namespace std;

string Encrypt(const string &inMessage,const  string &key)
{
	vector<string> blocs;
	// 1 - Transformer le message en tableau de blocs
	Blockify(inMessage, blocs);

	for(int i=0; i < blocs.size(); i++){
		cout << "Bloc Numero " << i << " : " << blocs.at(i);
	}

	// 2 
	
	return inMessage;
}

void Blockify( string& msg, vector<string>& blocs){


	int len = msg.length();
	int nbBlocs = len/4;
	if(len%4 != 0)
		nbBlocs++;

	for(int i=0; i < nbBlocs; i++){
		string cut = msg.substr(0,4);
		blocs.push_back(cut);

		for(int i = 0; i < 4; i++)
			msg.erase(0,1);

	}

	string tofill = blocs.at(blocs.size() - 1);
	if (tofill.length() < 8)
		tofill.resize(4, '0');
}