#include "header.hpp"

//Fonction main du hashage
string hashage(string& msg)
{
	vector<string> mblocs;
	vector<vector<bitset<8>>> grid;
	bitset<8> bnull(0x00);
	vector<bitset<8>> hashCode;
	vector<bitset<8>> hashCodeSecond;
	vector<bitset<8>> hashCodeFinal;
	//Transformation du message en block
	Blockify(msg, mblocs);
	//Transformation des block en matrice
	vstr_to_bitgrid(mblocs, grid);
	//Utilisation de la matrice pour le hashage
	//Utilisation du xor sur la matrice
	function_xor_hash(grid,hashCode);
	//Chiffrement de notre matrice de donnée qui pour créer ensuite un autre hashcode
	for(int i = 0; i < 3; i++)
	{
		mix_columns(grid);
		shift_rows(grid);
	}
	//Création d'un deuxième hashCode après chiffrement de la matrice
	function_xor_hash(grid,hashCodeSecond);
	//Xor sur nos deux hashcode pour créer notre hashCode final qui sera utilisé
	xor_between_2_hashcode(hashCode,hashCodeSecond,hashCodeFinal);
	return hashcode_to_str(hashCodeFinal);

}

//Fonction main du hashage 
void function_xor_hash(vector<vector<bitset<8>>> &grid, vector<bitset<8>> &hashCode)
{
	vector<vector<bitset<8>>> n_val;
	bitset<8> xorValue;
	vector<bitset<8>> p_hash;
	n_val = grid;
	for(int n = 0; n < n_val.size(); n++)
	{
		//Prend la valeur de chaque début de colonnes, prends la ligne du dessus et fait un xor entre.
		xorValue = xorValue^n_val.at(n).at(0);
		//Itération sur toute la colonne pour créer un bitset<8> provenant des opérations xor sur toute la colonne
		for(int m = 1; m < n_val.at(n).size(); m++)
		{
			xorValue = xorValue^n_val.at(n).at(m);
		}
		p_hash.push_back(xorValue);
	}
	hashCode = p_hash;
}

//Xor entre chaque bitset de nos deux hashcode pour brouiller les pistes
void xor_between_2_hashcode(vector<bitset<8>> &hashCode,vector<bitset<8>> &hashCodeSeconde, vector<bitset<8>> &hashCodeFinal)
{
	bitset<8> xorValue;
	vector<bitset<8>> p_hash;
	for(int n = 0; n < hashCode.size(); n++)
	{
		xorValue = hashCode.at(n)^hashCodeSeconde.at(n);
		p_hash.push_back(xorValue);
	}
	hashCodeFinal = p_hash;
}

//Convertit un hashCode de vector<bitset<8>> en string pour l'envoie sur le réseau
string hashcode_to_str(vector<bitset<8>> &hashCode){

	stringstream ss;

	for (int i=0; i < hashCode.size(); i++)
		ss << char(hashCode.at(i).to_ulong());
	return ss.str();
}

//Test si les hashCodes sont les mêmes pour l'intégrité du message
bool compare_hashcode(string hashCodeRecu,string monHashCode)
{
	if(hashCodeRecu == monHashCode)
		return true;
	return false;
}