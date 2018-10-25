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

	//mix_columns(grid);
	//bitset<8> a('k');
	//bitset<8> b('L');

	//bitset<8> c = gamul(a,b);
	//cout << "C gamuled =" << c << endl;



/*//////////////////////////////// Affichage pour le shift rows
	cout << "Original grid : " << endl;
	out_grid(grid);
	shift_rows(grid);
	cout << "Shifted with 1 : " << endl;
	out_grid(grid);
	shift_rows(grid, -1);
	cout << "Shifted with -1 : " << endl;
	out_grid(grid);
*/
	

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
/*
void unshift_rows(vector<vector<bitset<8>>> &grid){
	vector<vector<int>> landing_points;
	vector<vector<int>> landing_points_wf;

	vector<int> row;
	landing_points = generate_landing_points(grid);
	landing_points_wf = generate_landing_points(grid, -1 );

	out_2dint(landing_points);
	out_2dint(landing_points_wf);


}
*/
vector<vector<int>> generate_landing_points(vector<vector<bitset<8>>> &grid, int sfactor){

	vector<vector<int>> landing_points;
	vector<int> prow;
	vector<int> row;

	for (int i=0; i < grid.at(i).size(); i++){
		for (int n=0; n < grid.at(i).size(); n++){
			prow.push_back(n);
		}
	}

	for (int d=0; d < grid.at(d).size(); d++){
		for (int e=0; e < grid.at(d).size(); e++)
			row.push_back(prow[e + (sfactor * d)%grid.at(d).size()]);
		
		landing_points.push_back(row);
		row.clear();
	}
	return landing_points;

}
/*
bitset<8> gamul(bitset<8> a, bitset<8> b) {

	unsigned char c = char(a.to_ulong());
	unsigned char d = char(b.to_ulong());

	unsigned char p;
	unsigned char hi_bit_set;
	for(int i = 0; i < 8; i++) {
		if((d & 1) == 1) 
			p ^= c;
		hi_bit_set = (c & 0x80);
		c <<= 1;
		if(hi_bit_set == 0x80) 
			c ^= 0x1b;		
		d >>= 1;
	}
	bitset<8> r(p);
	return a^b;
}
*/
/*
void unmix_columns(vector<vector<bitset<8>>> &grid){

	vector<vector<bitset<8>>> cg;
	vector<vector<bitset<8>>> dg;
	vector<vector<bitset<8>>> recipient;
	vector<int> lp = {0,1,2,3};
	vector<bitset<8>> row;
	bitset<8> b;
	unsigned char h;

	cout << endl << "Matrice en entrée : " << endl << endl ;

	out_grid(grid);


	for (int i=0; i < grid.size(); i+=4){
		for (int n=0; n < grid.at(i).size(); n++){
		//cout << endl << "Valeur du bitset en i=" << i << " n=" << n  << " : ";
			cg.at(i).at(n) = grid.at(i).at(n);

			h = (unsigned char)(char(grid.at(i).at(n).to_ulong()) >> 7);
			dg.at(i).at(n) = grid.at(i).at(n) << 1;
			dg.at(i).at(n) ^= 0x1B & h;
		}

		recipient.at(i) = dg[lp[0]] ^ cg[lp[3]] ^ cg[lp[2]] ^ dg[lp[1]] ^ cg[lp[1]];
		recipient.at(i) = dg[lp[1]] ^ cg[lp[0]] ^ cg[lp[3]] ^ dg[lp[2]] ^ cg[lp[2]];
		recipient.at(i) = dg[lp[2]] ^ cg[lp[1]] ^ cg[lp[0]] ^ dg[lp[3]] ^ cg[lp[3]];
		recipient.at(i) = dg[lp[3]] ^ cg[lp[2]] ^ cg[lp[1]] ^ dg[lp[0]] ^ cg[lp[0]];
	}



	vector<vector<bitset<8>>> recipient;
	vector<bitset<8>> row;
	bitset<8> b;

	cout << endl << "Matrice en entrée reverse : " << endl << endl ;

	out_grid(grid);

	for (int i=0; i < grid.size(); i++){
		for (int n=0; n < grid.at(i).size(); n++){
		//cout << endl << "Valeur du bitset en i=" << i << " n=" << n  << " : ";

			b[0] = grid.at(i).at(n)[n];
			b[1] = grid.at(i).at(n)[(n+1)%grid.at(i).size()];
			b[2] = grid.at(i).at(n)[(n+2)%grid.at(i).size()];
			b[3] = grid.at(i).at(n)[(n+3)%grid.at(i).size()];
			b[4] = grid.at(i).at(n)[(n+4)%grid.at(i).size()];
			b[5] = grid.at(i).at(n)[(n+5)%grid.at(i).size()];
			b[6] = grid.at(i).at(n)[(n+6)%grid.at(i).size()];
			b[7] = grid.at(i).at(n)[(n+7)%grid.at(i).size()];


			row.push_back(b);
			b.reset();
			//cout << " | ";
		}
		recipient.push_back(row);
		row.clear();
		//cout << endl;
	}

	
	cout << "String unmixed : " << grid_to_str(recipient) ;
}
*/
/*
//	La fonction a été développée avec l'assistance de la page Wikipédia 
//	Rijndael MixColumns : https://en.wikipedia.org/wiki/Rijndael_MixColumns
void mix_columns(vector<vector<bitset<8>>> &grid){
	vector<vector<bitset<8>>> cg;
	vector<vector<bitset<8>>> dg;
	vector<vector<bitset<8>>> recipient;
	vector<int> lp = {0,1,2,3};
	vector<bitset<8>> row;
	bitset<8> b;
	unsigned char h;

	cout << endl << "Matrice en entrée : " << endl << endl ;

	out_grid(grid);


	for (int i=0; i < grid.size(); i+=4){
		for (int n=0; n < grid.at(i).size(); n++){
		//cout << endl << "Valeur du bitset en i=" << i << " n=" << n  << " : ";
			cg.at(i).at(n) = grid.at(i).at(n);

			h = (unsigned char)(char(grid.at(i).at(n).to_ulong()) >> 7);
			dg.at(i).at(n) = grid.at(i).at(n) << 1;
			dg.at(i).at(n) ^= 0x1B & h;
		}

		//recipient.at(i) = dg[lp[0]] ^ cg[lp[3]] ^ cg[lp[2]] ^ dg[lp[1]] ^ cg[lp[1]];
		//recipient.at(i) = dg[lp[1]] ^ cg[lp[0]] ^ cg[lp[3]] ^ dg[lp[2]] ^ cg[lp[2]];
		//recipient.at(i) = dg[lp[2]] ^ cg[lp[1]] ^ cg[lp[0]] ^ dg[lp[3]] ^ cg[lp[3]];
		//recipient.at(i) = dg[lp[3]] ^ cg[lp[2]] ^ cg[lp[1]] ^ dg[lp[0]] ^ cg[lp[0]];
	}

	cout << endl << "Matrice en sortie : " << endl << endl ;
	out_grid(recipient);

	cout << "After Mix : " << grid_to_str(recipient) << endl;
	unmix_columns(recipient);




/*

			b[0] = grid.at(i).at(n)[n];
			b[1] = grid.at(i).at((n+1)%grid.at(i).size())[n];
			b[2] = grid.at(i).at((n+2)%grid.at(i).size())[n];
			b[3] = grid.at(i).at((n+3)%grid.at(i).size())[n];
			b[4] = grid.at(i).at((n+4)%grid.at(i).size())[n];
			b[5] = grid.at(i).at((n+5)%grid.at(i).size())[n];
			b[6] = grid.at(i).at((n+6)%grid.at(i).size())[n];
			b[7] = grid.at(i).at((n+7)%grid.at(i).size())[n];

			//cout << "B :" << b ;

			for (int d=0; d < 8; d++){
				b[d] = grid.at(i).at((n + d)%grid.at(i).size())[d/4];
				//cout << b[d] << "[" << (n + d)%grid.at(i).size() << "," << d/4 << "]";


////////////// Modele de manipulation
				b[d] = grid.at(i).at(n)[0];
				b[d+1] = grid.at(i).at(n+1)[0];
				b[d+2] = grid.at(i).at(n+2)[0];
				b[d+3] = grid.at(i).at(n+3)[0];
				b[d+4] = grid.at(i).at(n)[1];
				b[d+5] = grid.at(i).at(n+1)[1];
				b[d+6] = grid.at(i).at(n+2)[1];
				b[d+7] = grid.at(i).at(n+3)[1];


				//cout << "<" << grid.at(n).at(d%grid.at(i).size()) << ">";
			}


			//%grid.at(i).at(n).size();

			//cout << "[" << i << "," << n << "] ";
			//cout << endl ;//<< "Bitmodel : <" ;
			
			for (int d=0; d < 8 ; d++){
				b[d] = grid.at(i).at((d)%grid.at(i).size())[(d)%grid.at(i).size()];
				//cout << (d)%grid.at(i).size() << ",";
				//recipient.at(i).at(n)[d] = grid.at(i).at((n+d)%grid.at(i).at(n).size())[0];
				
			}
			//cout << ">" << endl;

			
			row.push_back(b);
			b.reset();

			//cout << " | ";
		}
		recipient.push_back(row);
		row.clear();
		//cout << endl;
	}

	cout << endl << "Matrice en sortie : " << endl << endl ;
	out_grid(recipient);

	cout << "After Mix : " << grid_to_str(recipient) << endl;
	unmix_columns(recipient);



	vector<vector<bitset<8>>> copy_grid;
	vector<vector<bitset<8>>> doubled_grid;

	//unsigned char h;


	for (int i=0; i < grid.at(i).size(); i++){
		copy_grid[i] = grid[i];

		//h = (unsigned char)((signed char)grid[])
	}

}
*/

void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor){

	vector<bitset<8>> new_row;

	vector<vector<int>> landing_points;
	vector<int> row;
	landing_points = generate_landing_points(grid, sfactor);

	for (int i=0; i < grid.size(); i++){
		row = landing_points.at(i%grid.at(i).size());
		for (int n=0; n < grid.at(i).size(); n++){
			new_row.push_back(grid.at(i).at(row[n]));
		}
		

		grid.at(i) = new_row;
		new_row.clear();
	}

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

void out_grid(vector<vector<bitset<8>>> &grid){

	for (int i=0; i < grid.size() ; i++){
		cout << "Row " << i << "	: ";
		for (int j=0; j < grid.at(i).size(); j++){
			cout << grid.at(i).at(j) << " ";
		}
		cout << endl;
	}
}

void out_2dint(vector<vector<int>> &vec){

	for (int i=0; i < vec.size() ; i++){
		cout << "Row " << i << "	: ";
		for (int j=0; j < vec.at(i).size(); j++){
			cout << vec.at(i).at(j) << " ";
		}
		cout << endl;
	}
}