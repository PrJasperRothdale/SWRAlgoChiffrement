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
	Cipher(mblocs, kblocs);

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

void Cipher( vector<string> &blocs, vector<string> &key){

	vector<string> cryptogram;

	cout << "La taille de la clé est : " << key.size() << endl ;

	for(int i = 0; i < blocs.size(); i++){
		string cip = (blocs.at(i));
		cryptogram.push_back(cip);
	}

	for(int i=0; i < cryptogram.size(); i++){
		cout << "Bloc Numero " << i << " : " << cryptogram.at(i) << endl;
	}

	cout << endl << "This message by bytes:" << endl << endl << setbase(16);
	Bytify(cryptogram);


}

void Bytify( vector<string> &msg){

	vector<vector<int *>> byt_b;
	vector<int *> row;

	for(int i = 0; i < msg.size(); i++)
	{
		const char* c = msg.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;

		row.push_back(left);
		row.push_back(right);

		byt_b.push_back(row);

	}

	for(int i=0; i < byt_b.size(); i++){
		cout  << "Bytes :" << endl;
		for(int j=0; j < byt_b.at(i).size(); j++){
			cout  << " " << *byt_b.at(i).at(j);
			
		}
		cout << endl;
		
	}

}
/*
void printBytes(vector<string> v_s)
{
	vector<vector<int *>> byt_b;
	vector<int *> row;

	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		cout << "current c : " << c << endl;

		int* left = (int*)c;
		int* right = left+1;

		cout << "left : " << *left << " " << "|right : " << *right << " " << endl;

		row.push_back(left);
		row.push_back(right);

		byt_b.push_back(row);

	}

	for(int i=0; i < byt_b.size(); i++){
		for(int j=0; j < byt_b.at(i).size(); j++){
			cout  << "Bytes :" << *byt_b.at(i).at(j) << endl;
		}

		cout << endl;
	}

}
*/