void Hashage(string& msg)
{
	vector<string> mblocs;
	vector<vector<bitset<8>>> grid;
	bitset<8> bnull(0x00);
	vector<bitset<8>> hashCode;
	vector<bitset<8>> hashCodeSecond;
	vector<bitset<8>> hashCodeFinal;
	int nbBlocks = Blockify(msg, mblocs);
	cout << "Le nb de blocks par rapport au message est de " << nbBlocks;
	vstr_to_bitgrid(mblocs, grid);
	fctXOR_Hash(grid,hashCode);
	for(int i = 0; i < 3; i++)
	{
		mix_columns(grid);
		shift_rows(grid);
	}
	fctXOR_Hash(grid,hashCodeSecond);
	Xor2HashCode(hashCode,hashCodeSecond,hashCodeFinal);
	cout << "\nHashcode : " << hashCode_to_str(hashCodeFinal);
	cout << "\nHashcode 2: " << hashCode_to_str(hashCodeFinal);
	if(CompareHashcode(hashCodeFinal,hashCodeFinal))
		cout << "Message integre";
	else
		cout << "Message non integre";
	FormatSendHashCode(hashCodeFinal);

}


void fctXOR_Hash(vector<vector<bitset<8>>> &grid, vector<bitset<8>> &hashCode)
{
	vector<vector<bitset<8>>> n_val;
	bitset<8> xorValue;
	vector<bitset<8>> p_hash;
	n_val = grid;
	for(int n = 0; n < n_val.size(); n++)
	{
		xorValue = xorValue^n_val.at(n).at(0);
		for(int m = 1; m < n_val.at(n).size(); m++)
		{
			xorValue = xorValue^n_val.at(n).at(m);
		}
		p_hash.push_back(xorValue);
	}
	hashCode = p_hash;
	//cout << "end"<< hashCode_to_str(hashCode);
}

void Xor2HashCode(vector<bitset<8>> &hashCode,vector<bitset<8>> &hashCodeSeconde, vector<bitset<8>> &hashCodeFinal)
{
	bitset<8> xorValue;
	vector<bitset<8>> p_hash;
	for(int n = 0; n < hashCode.size(); n++)
	{
		xorValue = hashCode.at(n)^hashCodeSeconde.at(n);
		p_hash.push_back(xorValue);
	}
	hashCodeFinal = p_hash;
	cout << "Coucou\n";
}


string hashCode_to_str( vector<bitset<8>> &hashCode){

	stringstream ss;

	for (int i=0; i < hashCode.size(); i++)
		ss << char(hashCode.at(i).to_ulong());
	return ss.str();
}

bool CompareHashcode(vector<bitset<8>> &hashCodeRecu,vector<bitset<8>> &monHashCode)
{
	if(hashCode_to_str(hashCodeRecu) == hashCode_to_str(monHashCode))
		return true;
	return false;
}

void FormatSendHashCode(vector<bitset<8>> &hashCodeFinal)
{
	vector<bitset<8>> hashCodeFilled;
	hashCodeFilled = hashCodeFinal;
	bitset<8> bnull(0x00);
	cout << "\nLength hashcode : " <<  hashCodeFinal.size();
	cout << "\nLength hashcode 2 : " <<  hashCodeFilled.size();
	int nbCaract = hashCodeFinal.size();
	int nbFilled = 150 - hashCodeFinal.size();
	for(int i = 0; i < nbFilled; i++)
	{
		hashCodeFilled.push_back(bnull);
	}
	cout << "\nLength hashcode finale : " <<  hashCodeFilled.size();
}