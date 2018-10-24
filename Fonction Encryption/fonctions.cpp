#include "h.hpp"

using namespace std;

string Encrypt( string &msg, string &key)
{
	vector<string> mblocs;
	vector<string> kblocs;
	vector<vector<bitset<8>>> grid;


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

	grid = vstr_to_bitgrid(mblocs);
	shift_rows(grid);
	

	return msg;
}

int Blockify( string& msg, vector<string>& blocs){

	const int _taille_bloc_ = 4;

	int len = msg.length();
	int nbBlocs = len/_taille_bloc_;
	if(len%_taille_bloc_ != 0)
		nbBlocs++;

	for(int i=0; i < nbBlocs; i++){
		string cut = msg.substr(0,_taille_bloc_);
		blocs.push_back(cut);

		for(int i = 0; i < _taille_bloc_; i++)
			msg.erase(0,1);

	}

	string tofill = blocs.at(blocs.size() - 1);
	if (tofill.length() < _taille_bloc_)
		tofill.resize(_taille_bloc_, '0');

	return nbBlocs;
}

void Cipher( vector<string> &blocs, vector<string> &key){


	vector<string> cryptogram;

	//cout << "La taille de la clé est : " << key.size() << endl ;

	for(int i = 0; i < blocs.size(); i++){
		string cip = (blocs.at(i));
		cryptogram.push_back(cip);
	}
/*
	for(int i=0; i < cryptogram.size(); i++){
		cout << "Bloc Numero " << i << " : " << cryptogram.at(i) << endl;
	}
*/
	cout << endl << "This message by bytes:" << endl << endl << setbase(64);
	
	


}

void shift_rows(vector<vector<bitset<8>>> &grid){

	vector<int> landing_point;
	bitset<8> elem;
	vector<bitset<8>> new_row;

	for (int i=0; i < grid.size(); i++){
		for (int n=0; n < grid.at(i).size(); n++){

			switch (i % grid.at(i).size()) {
				case 0:{
					landing_point = {0,1,2,3};
					break;
				}
				case 1:{
					landing_point = {3,0,1,2};
					break;
				}
				case 2:{
					landing_point = {2,3,0,1};
					break;
				}
				case 3:{
					landing_point = {1,2,3,0};
					break;
				}
			}
			new_row.push_back(grid.at(i).at(landing_point[n]));
		}

		grid.at(i) = new_row;
		new_row.clear();


	}

/*////////////////////////////////////////////////////////////Affichage de la matrice
	cout << endl << "Bits AFTER SHIFTING :" << endl << endl;
	for (int i=0; i < grid.size() ; i++){
		//cout << "Row N°" << i << " :";
		for (int j=0; j < grid.at(i).size(); j++){
			cout << grid.at(i).at(j) << " ";
		}
		cout << endl << endl;
	}
*/

}

vector<vector<bitset<8>>> vstr_to_bitgrid(vector<string> &msg){

	vector<vector<bitset<8>>> grid;
	vector<bitset<8>> row;

	for (int x=0; x < msg.size(); x++){
		for (int e=0; e < msg.at(x).size(); e++){
			bitset<8> blet(msg.at(x).c_str()[e]);
			row.push_back(blet);
		}
		grid.push_back(row);
		row.clear();
	}
/*/////////////////////////////////////////////////////////////////////Affichage de la matrice
	cout << endl << "Bits BEFORE SHIFTING :" << endl << endl;
	for (int i=0; i < grid.size() ; i++){
		cout << "Row N°" << i << " :";
		for (int j=0; j < grid.at(i).size(); j++){
			cout << grid.at(i).at(j) << " ";
		}
		cout << endl;
	}
*/


	return grid;



/*///////////////////////////////////////////////ANCIEN CODE
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

	for(int j=0; j < byt_b.size(); j++){
		cout  << "Bytes :" << endl;
		for(int h=0; h < byt_b.at(j).size(); h++){
			cout  << " " << *byt_b.at(j).at(h);
			
		}
		cout << endl;
	}
*/

}

string grid_to_str( vector<vector<bitset<8>>> &grid){

	stringstream ss;

	for (int i=0; i < grid.size(); i++)
		for (int n=0; n < grid.at(i).size();n++)
			ss << char(grid.at(i).at(n).to_ulong());
		
	return ss.str();
}