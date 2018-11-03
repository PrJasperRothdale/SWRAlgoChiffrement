#include "header.hpp"

using namespace std;

//Fonction d'encryption symmetrique
string encrypt( string msg, string key)
{
	vector<string> mblocs;
	vector<string> kblocs;
	vector<vector<bitset<8>>> grid;
	vector<vector<bitset<8>>> grek;

	//Transformation de message en blocs puis en matrice d'octets
	Blockify(msg, mblocs);
	Blockify(key, kblocs);
	vstr_to_bitgrid(mblocs, grid);
	vstr_to_bitgrid(kblocs, grek);

	//Extension de la clé par replication pour avoir la même taille que le message
	extend_key_set(grid,grek);

	//Etapes de chiffrement répétées 13 fois
	cout << "\nAffichage de la grid avant nos etapes de chiffrement :\n";
	out_grid(grid);
	cout << "\n ----Début de notre chiffrement---- ";
	for (int i=0; i < 13; i++){
		mix_columns(grid);
		shift_rows(grid);
		cipher(grid,grek);
		cout << "\n\nAffichage de la grid à l'etape" << i << " de notre boucle:\n";
		out_grid(grid);
	}

	//Renvoi du message en forme string
	return grid_to_str(grid);

}

//Fonction de déchiffrement
string decrypt(string msg, string key){

	vector<string> mblocs;
	vector<string> kblocs;
	vector<vector<bitset<8>>> grid;
	vector<vector<bitset<8>>> grek;

	//Transformation en blocs puis en matrice d'octets
	Blockify(msg, mblocs);
	Blockify(key, kblocs);
	vstr_to_bitgrid(mblocs, grid);
	vstr_to_bitgrid(kblocs, grek);

	//Extension de la clé pour avoir la taille du message
	extend_key_set(grid,grek);

	cout << "\nAffichage de la grid avant nos etapes de dechiffrement :\n";
	out_grid(grid);
	cout << "\n ----Début de notre dechiffrement---- ";
	//Dechiffrement réalisé 13 fois
	for (int i=0; i < 13; i++){
		cipher(grid, grek);
		shift_rows(grid, -1);
		mix_columns(grid);
		cout << "\n\nAffichage de la grid à l'etape" << i << " de notre boucle:\n";
		out_grid(grid);
	}

	//Retour sous forme de string
	return grid_to_str(grid);
}

//Fonction de Transformation d'une string en tableau de blocs
void Blockify( string& msg, vector<string>& blocs){

	//Nombre de blocs
	const int taille = 4;

	int len = msg.length();
	int nbBlocs = len/taille;
	if(len%taille != 0)
		nbBlocs++;

	//Decoupage
	for(int i=0; i < nbBlocs; i++){
		string cut = msg.substr(0,taille);
		blocs.push_back(cut);

		//Suppression des parties traitées
		for(int i = 0; i < taille; i++)
			msg.erase(0,1);

	}


}

//Fonction de chiffrement par la clé
void cipher(vector<vector<bitset<8>>> &grid, vector<vector<bitset<8>>> &key){

	//Copie du message
	vector<vector<bitset<8>>> cg;
	cg = grid;

	//Application d'un ou exclusif entre la matrice clé et la matrice message
	for (int i=0; i < grid.size(); i++){
		for (int n=0; n < grid.at(i).size(); n++){
			cg.at(i).at(n) = grid.at(i).at(n) ^ key.at(i).at(n);
		}
	}
	
	grid = cg;
}

//Fonstion d'extension de la cle
void extend_key_set(vector<vector<bitset<8>>> &grid, vector<vector<bitset<8>>> &key){


	vector<vector<bitset<8>>> ck;
	int row = 0;
	int column = 0;

	//Initialisation par copie du message pour obtenir la taille de sortie désirée
	ck = grid;

	for (int i=0; i < grid.size(); i++){
		for (int n=0; n < grid.at(i).size(); n++){
			int s = key.size();
			int ss = key.at(i%s).size();
			int v = i%s;
			int w = n%ss;
			//Si la valeur en i,n est différente de la valeur de la clé (dimensions ajustées) on ecrase la valeur
			if ( ck.at(i).at(n) != key.at(v).at(w)){
				ck.at(i).at(n) = key.at(v).at(w);
			}
		}
	}
	key = ck;
}

//Fonction inutilisée dont le but aurait été d'appliquer la multiplication dans le champ de Galois d'AES
//L'opération MixColumns que nous réalisons n'étant pas la transformation de RijnDael elle ne sert pas
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
	return r;
}
*/

//Fonction qui étale l'information d'un octet sur toute sa colonne
void col_sign(vector<bitset<8>> &set){

	vector<bitset<8>> cset;
	cset = set;

	// La syntaxe est horrible car le developpeur a cassé son écran en essayant d'utiliser des expressions logiques
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

//Fonction qui répartit l'information de chaque octet sur tout les octets
void mix_columns(vector<vector<bitset<8>>> &grid){
	for (int i=0; i < grid.size(); i++){
		col_sign(grid.at(i));
	}
}

//Fonction qui génere des coordonnées pour la rotation des rangs
vector<vector<int>> lb_colshift(vector<vector<bitset<8>>> &grid, int sfactor){

	vector<vector<int>> landing_points;
	vector<int> prow;
	vector<int> row;

	//Rang symbolique, qui contient tous les indexs
	for (int i=0; i < grid.at(i).size(); i++){
		prow.push_back(i);
	}
	
	//Application de l'opération vers l'avant
	if (sfactor > 0)
	{
		for (int d=0; d < grid.size(); d++){
			for (int e=0; e < grid.at(d).size(); e++)
				row.push_back( (d + prow[e])%grid.size());

			landing_points.push_back(row);
			row.clear();
		}
	} // Si le facteur optionnel est négatif l'opération se fait vers l'arrière
	else
	{
		for (int d=0; d < grid.size(); d++){
			for (int e=0; e < grid.at(d).size(); e++){
				int v = (d - prow[e]);
				if (v < 0)
					v = grid.size() - (e - (d));
				row.push_back( (v)%grid.size());
			}
			landing_points.push_back(row);
			row.clear();
		}
	}

	return landing_points;
}

//Fonction qui décale les octets dans le rang
void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor){

	vector<vector<bitset<8>>> n_val;
	vector<bitset<8>> col;
	n_val = grid;
	vector<vector<int>> landing_points;

	//Récupération des coordonnées de destination
	landing_points = lb_colshift(grid, sfactor);

	for (int i=0; i < n_val.size() ; i++){
		for (int n=0; n < n_val.at(i).size(); n++){
			n_val.at(i).at(n) = grid.at(landing_points[i][n]).at(n);
		}
	}

	grid = n_val;
/* Fonctionnel - Supprimé lors du changement du sens de rotation de l'algorithme
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

//Fonction qui transforme un tableau de strings en matrice d'octets
void vstr_to_bitgrid(vector<string> &msg, vector<vector<bitset<8>>> &grid){

	vector<vector<bitset<8>>> cg;
	vector<bitset<8>> row;
	bitset<8> bnull(0x00);

	int d;
	
	for (int i=0; i < msg.size(); i++){
		for (int n=0 ; n < msg.at(i).size(); n++){
			bitset<8> blet(msg.at(i).c_str()[n]);
			row.push_back(blet);
		}
		cg.push_back(row);
		row.clear();
	}

	//Remplissage du dernier rang avec octet null pour avoir un matrice rectangulaire
	if ( cg.back().size() < cg.front().size()){
		d = cg.front().size() - cg.back().size();
		for (int x=0; x < d ; x++)
			cg.back().push_back(bnull);
		
	}

	grid = cg;
}

//Fonction d'interprétation de la matrice d'octet en string
string grid_to_str( vector<vector<bitset<8>>> &grid){

	stringstream ss;

	for (int i=0; i < grid.size(); i++)
		for (int n=0; n < grid.at(i).size();n++)
			ss << char(grid.at(i).at(n).to_ulong());
		
	return ss.str();
}

//Fonction d'affichage des matrice d'octets
void out_grid(vector<vector<bitset<8>>> &grid){

	for (int i=0; i < grid.size() ; i++){
		cout << "Row " << i << "	: ";
		for (int j=0; j < grid.at(i).size(); j++){
			cout << grid.at(i).at(j) << " ";
		}
		cout << endl;
	}
}

//Fonction d'affichage de matrice d'entier (les landing points par exemple)
void out_2dint(vector<vector<int>> &vec){

	for (int i=0; i < vec.size() ; i++){
		cout << "Row " << i << "	: ";
		for (int j=0; j < vec.at(i).size(); j++){
			cout << vec.at(i).at(j) << " ";
		}
		cout << endl;
	}
}