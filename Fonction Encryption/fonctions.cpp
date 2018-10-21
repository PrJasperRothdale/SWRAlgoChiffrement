#include "h.hpp"

using namespace std;

string Encrypt( string &msg, string &key)
{
	vector<string> mblocs;
	vector<string> kblocs;
	// 1 - Transformer le message en tableau de blocs
	int nbB = Blockify(msg, mblocs);
	int nbBK = Blockify(key, kblocs);

	cout << "NB Blocs message est : " << nbB << endl;
	cout << "NB blocs clé est : " << nbBK << endl;

	for(int i=0; i < mblocs.size(); i++){
		cout << "Bloc Numero " << i << " : " << mblocs.at(i) << endl;
	}

	for(int i=0; i < kblocs.size(); i++){
		cout << "Bloc Numero " << i << " : " << kblocs.at(i) << endl;
	}

	// 2 - Chiffrer le tableau
	//Cipher(mblocs, kblocs);

	return msg;
}

int Blockify( string& msg, vector<string>& blocs){

	int len = msg.length();
	int nbBlocs = len/8;
	if(len%8 != 0)
		nbBlocs++;

	for(int i=0; i < nbBlocs; i++){
		string cut = msg.substr(0,8);
		blocs.push_back(cut);

		for(int i = 0; i < 8; i++)
			msg.erase(0,1);

	}

	string tofill = blocs.at(blocs.size() - 1);
	if (tofill.length() < 8)
		tofill.resize(8, '0');

	return nbBlocs;
}
/*
void Cipher( vector<string> &blocs, vector<string> &key){

	vector<string> cryptogram;

	cout << "La taille de la clé est : " << key.size() << endl ;

	for(int i = 0; i < blocs.size(); i++){
		string cip = blocs.at(i);
		cryptogram.push_back();
	}

	for(int i=0; i < cryptogram.size(); i++){
		cout << "Bloc Numero " << i << " : " << cryptogram.at(i) << endl;
	}


}*/