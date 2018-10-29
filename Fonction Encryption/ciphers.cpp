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
	cout << "Texte : <" << grid_to_str(grid) << ">";
	//cout << endl << endl << "Avant Shifting :" << endl;
	//out_grid(grid);


	cout << endl << "Matrice input :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	//mix_columns(grid);
	shift_rows(grid);
	cout << endl << "Crypto 1 :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	//mix_columns(grid);
	shift_rows(grid);
	cout << endl << "Crypto 2 :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	//mix_columns(grid);
	shift_rows(grid);
	cout << endl << "Crypto 3 :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	shift_rows(grid, -1);
	//mix_columns(grid);
	cout << endl << "Crypto -3 :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	shift_rows(grid, -1);
	//mix_columns(grid);
	cout << endl << "Crypto -2 :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	shift_rows(grid, -1);
	//mix_columns(grid);
	cout << endl << "Crypto -1 :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";

	//shift_rows(grid, -1);
	//mix_columns(grid);
	cout << endl << "Matrice out :" << endl;
	out_grid(grid);
	cout << "Texte : <" << grid_to_str(grid) << ">";


	//shift_rows(grid, -1);
	//cout << endl << endl << "Apres Shifting :" << endl;
	//out_grid(grid);
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
/*
	string tofill = blocs.at(blocs.size() - 1);
	if (tofill.length() < _taille_bloc_)
		tofill.resize(_taille_bloc_, '0');
*/
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

/////////////////////////////////////////////////////////////////////////////// Ancienne gen lp
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


void row_sign(vector<bitset<8>> &set){

	vector<bitset<8>> cset;

	cset = set;

	cset[0][7] = set[0][7];
	cset[0][6] = set[0][6];
	cset[0][5] = set[1][7];
	cset[0][4] = set[1][6];
	cset[0][3] = set[2][7];
	cset[0][2] = set[2][6];
	cset[0][1] = set[3][7];
	cset[0][0] = set[3][6];

	cset[1][7] = set[0][5];
	cset[1][6] = set[0][4];
	cset[1][5] = set[1][5];
	cset[1][4] = set[1][4];
	cset[1][3] = set[2][5];
	cset[1][2] = set[2][4];
	cset[1][1] = set[3][5];
	cset[1][0] = set[3][4];	

	cset[2][7] = set[0][3];
	cset[2][6] = set[0][2];
	cset[2][5] = set[1][3];
	cset[2][4] = set[1][2];
	cset[2][3] = set[2][3];
	cset[2][2] = set[2][2];
	cset[2][1] = set[3][3];
	cset[2][0] = set[3][2];

	cset[3][7] = set[0][1];
	cset[3][6] = set[0][0];
	cset[3][5] = set[1][1];
	cset[3][4] = set[1][0];
	cset[3][3] = set[2][1];
	cset[3][2] = set[2][0];
	cset[3][1] = set[3][1];
	cset[3][0] = set[3][0];

	set = cset;

}

void mix_columns(vector<vector<bitset<8>>> &grid){

	for (int i=0; i < grid.size(); i++){
		row_sign(grid.at(i));
	}

}




vector<vector<int>> lb_colshift(vector<vector<bitset<8>>> &grid, int sfactor){

	vector<vector<int>> landing_points;
	vector<int> prow;
	vector<int> row;


	for (int i=0; i < grid.at(i).size(); i++){
		prow.push_back(i);
	}
	
	if (sfactor > 0){
		for (int d=0; d < grid.size(); d++){
			for (int e=0; e < grid.at(d).size(); e++)
				row.push_back( (d + prow[e])%grid.size());

			landing_points.push_back(row);
			row.clear();
		}
	} else if (sfactor < 0){
		for (int d=0; d < grid.size(); d++){
			for (int e=0; e < grid.at(d).size(); e++){
				int v = (d - prow[e]);
				if (v < 0)
					v = ((d - prow[e])%grid.size())+grid.at(d).size();
				row.push_back( (v)%grid.size());
			}
			landing_points.push_back(row);
			row.clear();
		}
	}
/*
	for (int d=0; d < grid.size(); d++){
		for (int e=0; e < grid.at(d).size(); e++)
			row.push_back( (d + prow[e])%grid.size());
		
		landing_points.push_back(row);
		row.clear();
	}
*/
	//cout << endl << "Land points : " << endl;
	//out_2dint(landing_points);

	return landing_points;

}

void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor){

	vector<vector<bitset<8>>> n_val;
	vector<bitset<8>> col;
	n_val = grid;
	vector<vector<int>> landing_points;

	landing_points = lb_colshift(grid, sfactor);

	for (int i=0; i < n_val.size() ; i++){
		for (int n=0; n < n_val.at(i).size(); n++){
			n_val.at(i).at(n) = grid.at(landing_points[i][n]).at(n);

		}
	}

	grid = n_val;

/* WORKING - Removed during coding
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
*/
}

vector<vector<bitset<8>>> vstr_to_bitgrid(vector<string> &msg){

	vector<vector<bitset<8>>> grid;
	vector<bitset<8>> row;
	bitset<8> bnull(0x00);

	int d;

	for (int i=0; i < msg.size(); i++){
		for (int n=0 ; n < msg.at(i).size(); n++){
			bitset<8> blet(msg.at(i).c_str()[n]);
			row.push_back(blet);
		}
		grid.push_back(row);
		row.clear();
	}

	if ( grid.back().size() < grid.front().size()){
		d = grid.front().size() - grid.back().size();
		for (int x=0; x < d ; x++)
			grid.back().push_back(bnull);
		
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